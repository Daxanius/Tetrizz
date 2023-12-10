#pragma once
#include <Core.h>
#include <vector>
#include "GameDefines.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Tetrominos.h"
#include "CameraManager.h"
#include "AnimatedText.h"
#include "GameScreen.h"

struct ScoreText
{
  AnimatedText animatedText;
  int          score;
};

class TetrizzScreen : public GameScreen
{
public:
  TetrizzScreen(ScreenManager* screenManager);
  ~TetrizzScreen();

  // From it's abstract declarations
  void Draw();

  void Update(float deltaTime);

  void FixedUpdate(float fixedDeltaTime);

  void OnKeyDownEvent(SDL_Keycode key);

  void OnKeyUpEvent(SDL_Keycode key) {};

  // Unused in TerizzScreen
  void OnMouseMotionEvent(const SDL_MouseMotionEvent& e) {};

  void OnMouseDownEvent(const SDL_MouseButtonEvent& e) {};

  void OnMouseUpEvent(const SDL_MouseButtonEvent& e) {};

private:
  // Variables
  ScreenManager* m_ScreenManager;

  Mix_Chunk* m_MusicPtr;
  Mix_Chunk* m_WelcomePtr;
  Mix_Chunk* m_PlacePtr;
  Mix_Chunk* m_ClearPtr;
  Mix_Chunk* m_RotatePointer;
  Mix_Chunk* m_SmallRizzlerPtr;
  Mix_Chunk* m_LilBitOfRizzPtr;
  Mix_Chunk* m_YouGotRizzPtr;
  Mix_Chunk* m_TetRizzPtr;
  Mix_Chunk* m_GameOverPtr;
  Mix_Chunk* m_DeathPtr;
  Mix_Chunk* m_ScorePtr;

  CameraManager* m_CameraManager;
  Playfield* m_PlayfieldPtr;

  std::vector<ScoreText> m_ScoreTextEffects;

  bool       m_GameOver{};
  int        m_TickCount{};

  int        m_Score{ 0 };

  // Declare your own functions here
  void PlaceTetromino();

  void DrawSaved(const Point2f& position);
  void DrawNext(const Point2f& position);
  void AddToScore(int value);
};