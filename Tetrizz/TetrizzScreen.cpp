#include "pch.h"
#include "TetrizzScreen.h"
#include "MenuScreen.h"
#include "Resource.h"

TetrizzScreen::TetrizzScreen(ScreenManager* screenManager, Difficulty difficulty)
{
  m_ScreenManager = screenManager;
  m_Difficulty = difficulty;
  m_TicksPerUpdate = TICKS_PER_UPDATE / m_Difficulty;

  m_MusicPtr = Mix_LoadWAV(THEME_GAME);
  m_WelcomePtr = Mix_LoadWAV(FX_START);
  m_PlacePtr = Mix_LoadWAV(FX_PLACE);
  m_RotatePointer = Mix_LoadWAV(FX_ROTATE);
  m_SmallRizzlerPtr = Mix_LoadWAV(FX_CLEAR_1);
  m_LilBitOfRizzPtr = Mix_LoadWAV(FX_CLEAR_2);
  m_YouGotRizzPtr = Mix_LoadWAV(FX_CLEAR_3);
  m_TetRizzPtr = Mix_LoadWAV(FX_CLEAR_4);
  m_GameOverPtr = Mix_LoadWAV(FX_GAME_OVER);
  m_DeathPtr = Mix_LoadWAV(THEME_GAME_OVER);
  m_ScorePtr = Mix_LoadWAV(FX_SCORE);

  Mix_PlayChannel(0, m_MusicPtr, -1);
  Mix_PlayChannel(-1, m_WelcomePtr, 0);

  m_CameraManager = CameraManager();
  m_PlayfieldPtr = new Playfield(TETROMINOS_ARR, TETROMINO_COUNT);
}

TetrizzScreen::~TetrizzScreen()
{
  // free game resources here
  delete m_PlayfieldPtr;
  m_ScoreTextEffects.clear();

  Mix_FreeChunk(m_MusicPtr);
  Mix_FreeChunk(m_WelcomePtr);
  Mix_FreeChunk(m_PlacePtr);
  Mix_FreeChunk(m_RotatePointer);
  Mix_FreeChunk(m_SmallRizzlerPtr);
  Mix_FreeChunk(m_LilBitOfRizzPtr);
  Mix_FreeChunk(m_YouGotRizzPtr);
  Mix_FreeChunk(m_TetRizzPtr);
  Mix_FreeChunk(m_GameOverPtr);
  Mix_FreeChunk(m_DeathPtr);
  Mix_FreeChunk(m_ScorePtr);
}

// Put your own draw statements here
void TetrizzScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  const float boardWidthOffset = (TILE_SIZE * FIELD_WIDTH) / 2.f;
  const float boardHeightOffset = (TILE_SIZE * FIELD_HEIGHT) / 2.f;

  DrawSaved(Point2f{ boardWidthOffset , boardHeightOffset });
  DrawNext(Point2f{ windowSettings.width - boardWidthOffset - 30, boardHeightOffset });

  m_PlayfieldPtr->Draw({ centerX - boardWidthOffset, centerY - boardHeightOffset });

  DrawString("Rizz: " + std::to_string(m_Score), Point2f{ 10, 0 }, 40, { 1.0 , 1.0 ,1.0 , 1.0 }, FONT_MAIN);

  for (ScoreText scoreText : m_ScoreTextEffects) {
    scoreText.animatedText.Draw();
  }

  if (m_GameOver)
  {
    Rectf sourceRect{};
    sourceRect.top = 0;
    sourceRect.left = 0;
    sourceRect.width = windowSettings.width;
    sourceRect.height = windowSettings.height;

    SetColor({ 1.0 , 0.0 , 0.0 , 0.5 });
    FillRect(sourceRect);

    DrawString("Game Over!", Point2f{ centerX - 105 ,centerY - 75 }, 50, { 1.0 , 1.0 ,1.0 , 1.0 }, FONT_MAIN);
    DrawString("Press 'R' to Reset", Point2f{ centerX - 155 ,centerY - 15 }, 50, { 1.0 , 1.0 ,1.0 , 1.0 }, FONT_MAIN);
  }
}

void TetrizzScreen::Update(float deltaTime)
{
  for (size_t i = 0; i < m_ScoreTextEffects.size(); ++i) {
    m_ScoreTextEffects[i].animatedText.Update(deltaTime);

    if (m_ScoreTextEffects[i].animatedText.GetGoalsLeft() < 1) {
      Mix_PlayChannel(-1, m_ScorePtr, 0);
      m_Score += m_ScoreTextEffects[i].score;
      m_ScoreTextEffects.erase(m_ScoreTextEffects.begin() + i);
    }
  }
}

void TetrizzScreen::FixedUpdate(float fixedDeltaTime)
{
  if (m_TickCount % m_TicksPerUpdate == 0 && !m_GameOver) {
    if (!m_PlayfieldPtr->CanMove({ 0, 1 }))
    {
      PlaceTetromino();
    } else {
      m_PlayfieldPtr->Move({ 0, 1 });
    }
  }

  m_CameraManager.Update();
  ++m_TickCount;
}
#pragma endregion gameFunctions

#pragma region inputHandling											
void TetrizzScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    m_ScreenManager->SetScreen(new MenuScreen(m_ScreenManager));
    return;
  }

  if (m_GameOver) {
    if (key == SDLK_r)
    {
      m_PlayfieldPtr->ResetBoard();
      m_ScoreTextEffects.clear();
      m_GameOver = false;
      m_Score = 0;
      Mix_PlayChannel(0, m_MusicPtr, -1);
    }
    return;
  }

  switch (key)
  {
  case SDLK_LEFT:
    m_PlayfieldPtr->Move({ -1, 0 });
    break;
  case SDLK_RIGHT:
    m_PlayfieldPtr->Move({ 1, 0 });
    break;
  case SDLK_UP:
    if (m_PlayfieldPtr->Move({ 0, 0 }, 1)) {
      Mix_PlayChannel(-1, m_RotatePointer, 0);
      m_PlayfieldPtr->Move({ 0, 0 });
    }

    break;
  case SDLK_DOWN:
    m_PlayfieldPtr->Move({ 0, 1 });
    AddToScore(1);
    break;
  case SDLK_SPACE:
  {
    int multiplier = m_PlayfieldPtr->GetQuickPlacePosition().y - m_PlayfieldPtr->GetState()->GetTetrominoPosition().y;
    m_PlayfieldPtr->QuickPlace();
    AddToScore(2 * multiplier);
    PlaceTetromino();
    break;
  }
  case SDLK_c:
    if (m_PlayfieldPtr->m_CanSaveTetromino && m_PlayfieldPtr->GetState()->GetSavedTetromino() != m_PlayfieldPtr->GetState()->GetTetrominoIndex())
    {
      m_PlayfieldPtr->SaveTetromino();
      m_PlayfieldPtr->m_CanSaveTetromino = false;
    }
    break;
  }
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void TetrizzScreen::PlaceTetromino()
{
  if (!m_PlayfieldPtr->PlaceTetromino()) {
    m_GameOver = true;
    Mix_PlayChannel(-1, m_GameOverPtr, 0);
    Mix_PlayChannel(0, m_DeathPtr, -1);
    return;
  }

  Mix_PlayChannel(-1, m_PlacePtr, 0);
  float intensity{};

  int linesCleaared = m_PlayfieldPtr->ClearFullLines();

  if (linesCleaared > 0) {
    m_TicksPerUpdate = std::max(1, m_TicksPerUpdate + SPEEDUP_PER_CLEAR * m_Difficulty);
  }

  switch (linesCleaared)
  {
  case 1:
    Mix_PlayChannel(-1, m_SmallRizzlerPtr, 0);
    intensity = 1;
    AddToScore(intensity * (intensity * LINE_CLEAR_SCORE));
    break;
  case 2:
    Mix_PlayChannel(-1, m_LilBitOfRizzPtr, 0);
    intensity = 2;
    AddToScore(intensity * (intensity * LINE_CLEAR_SCORE));
    break;
  case 3:
    Mix_PlayChannel(-1, m_YouGotRizzPtr, 0);
    intensity = 3;
    AddToScore(intensity * (intensity * LINE_CLEAR_SCORE));
    break;
  case 4:
    Mix_PlayChannel(-1, m_TetRizzPtr, 0);
    intensity = 4;
    AddToScore(intensity * (intensity * LINE_CLEAR_SCORE));
    break;
  default:
    break;
  }

  m_CameraManager.SetShake(intensity, 10);

  m_PlayfieldPtr->MoveLinesDown();
  m_PlayfieldPtr->NextTetromino();

  m_PlayfieldPtr->m_CanSaveTetromino = true;
}

void TetrizzScreen::DrawSaved(const Point2f& position)
{
  Rectf sourceRect{};
  sourceRect.height = 120;
  sourceRect.width = 120;
  sourceRect.top = position.y - 40;
  sourceRect.left = position.x - int(sourceRect.width / 3);

  SetColor({ 0.0 ,0.0 , 0.0 ,1.0 });
  FillRect(sourceRect);

  SetColor({ 1.0 ,1.0 , 1.0 ,1.0 });
  for (int lineThickness{}; lineThickness < 10; lineThickness++)
  {
    Rectf outlineRect;
    outlineRect.height = sourceRect.height + lineThickness;
    outlineRect.width = sourceRect.width + lineThickness;
    outlineRect.top = sourceRect.top + ceil(lineThickness / 2);
    outlineRect.left = sourceRect.left + ceil(lineThickness / 2);

    DrawRect(outlineRect);
  }

  const int indexOfSavedTetromino{ m_PlayfieldPtr->GetState()->GetSavedTetromino() };

  if (indexOfSavedTetromino > -1)
  {
    Tetromino* savedTetromino{ new Tetromino(TETROMINOS_ARR[indexOfSavedTetromino]) };
    savedTetromino->Draw({ position.x , position.y });

    delete savedTetromino;
  }

  DrawString("Saved", { position.x - 12, position.y - 50 }, 30, { 1.0 ,1.0 ,1.0 }, FONT_MAIN);
}

void TetrizzScreen::DrawNext(const Point2f& position)
{
  Rectf sourceRect;
  sourceRect.height = 120;
  sourceRect.width = 120;
  sourceRect.top = position.y - 40;
  sourceRect.left = position.x - int(sourceRect.width / 3);

  SetColor({ 0.0 ,0.0 , 0.0 ,1.0 });
  FillRect(sourceRect);

  SetColor({ 1.0 ,1.0 , 1.0 ,1.0 });
  for (int lineThickness{}; lineThickness < 10; lineThickness++)
  {
    Rectf outlineRect;
    outlineRect.height = sourceRect.height + lineThickness;
    outlineRect.width = sourceRect.width + lineThickness;
    outlineRect.top = sourceRect.top + ceil(lineThickness / 2);
    outlineRect.left = sourceRect.left + ceil(lineThickness / 2);

    DrawRect(outlineRect);
  }

  const int indexOfNextTetromino{ m_PlayfieldPtr->GetState()->GetQueuedTetromino() };
  Tetromino* nextTetromino{ new Tetromino(TETROMINOS_ARR[indexOfNextTetromino]) };
  nextTetromino->Draw({ position.x , position.y });

  delete nextTetromino;

  DrawString("Next", { position.x - 4, position.y - 50 }, 30, { 1.0 ,1.0 ,1.0 }, FONT_MAIN);
}

void TetrizzScreen::AddToScore(int value)
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  const float boardWidthOffset = (TILE_SIZE * FIELD_WIDTH) / 2.f;
  const float boardHeightOffset = (TILE_SIZE * FIELD_HEIGHT) / 2.f;

  Point2f startPosition{
    m_PlayfieldPtr->GetState()->GetTetrominoPosition().x * TILE_SIZE + (centerX - boardWidthOffset),
    m_PlayfieldPtr->GetState()->GetTetrominoPosition().y * TILE_SIZE + (centerY - boardHeightOffset)
  };

  AnimatedText textAnim = AnimatedText(
    startPosition,
    "+" + std::to_string(value),
    0,
    { 0.1f, 1.f, 0.1f, 1.f },
    FONT_MAIN
  );

  textAnim.AddGoal(
    {
      startPosition,
      { 0.1f, 1.f, 0.1f, 1.f },
      30,
      1,
      0,
    }
  );

  textAnim.AddGoal(
    {
      { 80.f, 35.f },
      { 0.1f, 1.f, 0.1f, 1.f },
      30,
      1,
      0,
    }
  );

  m_ScoreTextEffects.push_back(
    {
      textAnim,
      value
    }
  );
}