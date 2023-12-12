#pragma once
#include <Core.h>
#include "GameScreen.h"
#include "TetrizzScreen.h"
#include "MenuScreen.h"
#include "Utils.h"
#include "Button.h"

class DifficultyScreen : public GameScreen
{
public:
  DifficultyScreen(ScreenManager* screenManager);
  ~DifficultyScreen();

  void Draw();

  void Update(float deltaTime);

  void FixedUpdate(float fixedDeltaTime) {};

  void OnKeyDownEvent(SDL_Keycode key);

  void OnKeyUpEvent(SDL_Keycode key) {};

  void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);

  void OnMouseDownEvent(const SDL_MouseButtonEvent& e);

  void OnMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
  ScreenManager* m_ScreenManager;

  Button* m_EasyButton;
  Button* m_PlayButton;
  Button* m_HardButton;
  Button* m_BackButton;
};