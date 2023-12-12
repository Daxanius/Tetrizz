#pragma once
#include <Core.h>
#include "GameScreen.h"
#include "TetrizzScreen.h"
#include "Utils.h"
#include "Button.h"

class CreditsScreen : public GameScreen
{
public:
  CreditsScreen(ScreenManager* screenManager);
  ~CreditsScreen();

  // From it's abstract declarations
  void Draw();

  void Update(float deltaTime);

  void FixedUpdate(float fixedDeltaTime);

  void OnKeyDownEvent(SDL_Keycode key);

  void OnKeyUpEvent(SDL_Keycode key);

  void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);

  void OnMouseDownEvent(const SDL_MouseButtonEvent& e);

  void OnMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
  // Variables
  ScreenManager* m_ScreenManager;
  
  Button* m_BackButton;
};

