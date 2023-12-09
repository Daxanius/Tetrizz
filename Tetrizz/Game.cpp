#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions
void Start()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 4, 2048) < 0) {
		std::cerr << "SDL Mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
		SDL_Quit(); // Quit SDL if Mixer initialization fails
	}

	g_MusicPtr = Mix_LoadWAV("../Resources/theme.wav");
  g_WelcomePtr = Mix_LoadWAV("../Resources/welcome.wav");
  g_PlacePtr = Mix_LoadWAV("../Resources/place.wav");
  g_RotatePointer = Mix_LoadWAV("../Resources/rotate.wav");
  g_SmallRizzlerPtr = Mix_LoadWAV("../Resources/small_rizzler.wav");
  g_LilBitOfRizzPtr = Mix_LoadWAV("../Resources/lil_bit_of_rizz.wav");
  g_YouGotRizzPtr = Mix_LoadWAV("../Resources/you_got_rizz.wav");
  g_TetRizzPtr = Mix_LoadWAV("../Resources/tet_rizz.wav");
  g_GameOverPtr = Mix_LoadWAV("../Resources/game_over.wav");


  Mix_PlayChannel(-1, g_WelcomePtr, 0);
  Mix_PlayChannel(0, g_MusicPtr, -1);

  SDL_DisplayMode displayMode{ GetDisplayMode() };
  const float sizeX{ 800.f };
  const float sizeY{ 600.f };

  WindowSettings window{
      "Tetrizz - Balder Huybreghs & Quentin Demuynck - 1DAE16", // title
      0,                                         // Fullscreen mode (SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN, 0)
      sizeX,                                     // width
      sizeY,                                     // height
      int(displayMode.w / 2) - int(sizeX / 2),   // posX
      int(displayMode.h / 2) - int(sizeY / 2),   // posY
      1.f,                                       // opacity
      true,                                      // vsync
      true,                                      // lineSmoothing
      false,                                     // alwaysOnTop
      true                                       // bordered
  };

  // [DYSON] Creates a window, you can call this as many times as you want
  // to create a bunch of windows, just make sure to use SelectWindow(int id) to
  // select the window to update and draw to. 
  // This function returns the int id of the window created
  MakeWindow(window);

	// initialize game resources here
  // TextureFromFile("Resources/dyson.png", g_Texture);
  g_PlayfieldPtr = new Playfield(TETROMINOS_ARR, TETROMINO_COUNT);
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();
  
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  const float boardWidthOffset = (TILE_SIZE * FIELD_WIDTH) / 2.f;
  const float boardHeightOffset = (TILE_SIZE * FIELD_HEIGHT) / 2.f;

  DrawSaved(Point2f{ boardWidthOffset , boardHeightOffset });
  DrawNext(Point2f{ windowSettings.width - boardWidthOffset - 30, boardHeightOffset });

  g_PlayfieldPtr->Draw( { centerX - boardWidthOffset, centerY - boardHeightOffset } );

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{

}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  if (g_TickCount % TICKS_PER_UPDATE == 0 && !g_GameOver) {
    if (!g_PlayfieldPtr->CanMove({ 0, 1 }))
    {
      PlaceTetromino();
    } else {
      g_PlayfieldPtr->Move({ 0, 1 });
    }
  }

  ++g_TickCount;
}

void End()
{
	// free game resources here
  delete g_PlayfieldPtr;
  g_PlayfieldPtr = nullptr;
  Mix_CloseAudio();
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
  if (g_GameOver) {
    return;
  }

  switch (key)
  {
  case SDLK_LEFT:
    g_PlayfieldPtr->Move({ -1, 0 });
	  break;
  case SDLK_RIGHT:
    g_PlayfieldPtr->Move({ 1, 0 });
	  break;
  case SDLK_UP:
    if (g_PlayfieldPtr->Move({ 0, -1 }, 1)) {
      Mix_PlayChannel(-1, g_RotatePointer, 0);
    }
  case SDLK_DOWN:
    g_PlayfieldPtr->Move({ 0, 1 });
    break;
  case SDLK_SPACE:
    g_PlayfieldPtr->QuickPlace();
    PlaceTetromino();
    break;
  case SDLK_c:
    g_PlayfieldPtr->SaveTetromino();
	  break;
  }
}

void OnKeyUpEvent(SDL_Keycode key)
{
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	// SAMPLE CODE: print mouse position
	//const float mouseX{ float(e.x) };
	//const float mouseY{ float(e.y) };
	//std::cout << "  [" << mouseX << ", " << mouseY << "]\n";
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	// SAMPLE CODE: print mouse position
	//const float mouseX{ float(e.x) };
	//const float mouseY{ float(e.y) };
	//std::cout << "  [" << mouseX << ", " << mouseY << "]\n";
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	// SAMPLE CODE: print mouse position
	//const float mouseX{ float(e.x) };
	//const float mouseY{ float(e.y) };
	//std::cout << "  [" << mouseX << ", " << mouseY << "]\n";
	
	// SAMPLE CODE: check which mouse button was pressed
	//switch (e.button)
	//{
	//case SDL_BUTTON_LEFT:
	//	//std::cout << "Left mouse button released\n";
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	//std::cout << "Right mouse button released\n";
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	//std::cout << "Middle mouse button released\n";
	//	break;
	//}
}
#pragma endregion inputHandling

#pragma region ownDefinitions
void PlaceTetromino()
{
  if (!g_PlayfieldPtr->PlaceTetromino()) {
    g_GameOver = true;
    Mix_PlayChannel(-1, g_GameOverPtr, 0);
    Mix_HaltChannel(0);
    return;
  }

  Mix_PlayChannel(-1, g_PlacePtr, 0);

  switch (g_PlayfieldPtr->ClearFullLines())
  {
  case 1:
	  Mix_PlayChannel(-1, g_SmallRizzlerPtr, 0);
	  break;
  case 2:
	  Mix_PlayChannel(-1, g_LilBitOfRizzPtr, 0);
	  break;
  case 3:
	  Mix_PlayChannel(-1, g_YouGotRizzPtr, 0);
	  break;
  case 4:
	  Mix_PlayChannel(-1, g_TetRizzPtr, 0);
	  break;
  default:
	  break;
  }

  g_PlayfieldPtr->MoveLinesDown();
  g_PlayfieldPtr->NextTetromino();
}

void DrawString(const std::string& output , const Point2f topLeft, const int fontSize, const Color4f& color, const std::string& fontLocation)
{
	Texture texturePtr;
	TextureFromString(output, fontLocation, fontSize, color, texturePtr);
	DrawTexture(texturePtr, topLeft);
  DeleteTexture(texturePtr);
}

void DrawSaved(const Point2f& position)
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
		outlineRect.top = sourceRect.top + ceil(lineThickness/2);
		outlineRect.left = sourceRect.left + ceil(lineThickness / 2);

		DrawRect(outlineRect);
	}

	const int indexOfSavedTetromino{ g_PlayfieldPtr->GetState()->GetSavedTetromino() };

	if (indexOfSavedTetromino > -1)
	{
		Tetromino* savedTetromino{ new Tetromino(TETROMINOS_ARR[indexOfSavedTetromino]) };
		savedTetromino->Draw({ position.x , position.y });

		delete savedTetromino;
	}

	DrawString("Saved", { position.x - 12, position.y - 50 }, 30, { 1.0 ,1.0 ,1.0 }, "Resources/dhurjati.otf");
}

void DrawNext(const Point2f& position)
{
	Rectf sourceRect;
	sourceRect.height = 120;
	sourceRect.width  = 120;
	sourceRect.top    = position.y - 40;
	sourceRect.left   = position.x - int(sourceRect.width / 3);

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

	const int indexOfNextTetromino{ g_PlayfieldPtr->GetState()->GetQueuedTetromino() };
	Tetromino* nextTetromino{ new Tetromino(TETROMINOS_ARR[indexOfNextTetromino]) };
	nextTetromino->Draw({ position.x , position.y });

	delete nextTetromino;

	DrawString("Next", {position.x - 4, position.y - 50}, 30, {1.0 ,1.0 ,1.0}, "Resources/dhurjati.otf");
}

#pragma endregion ownDefinitions