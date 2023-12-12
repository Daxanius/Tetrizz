#pragma once
#include <Core.h>
#include "GameScreen.h"
#include "TetrizzScreen.h"
#include "Utils.h"
#include "Button.h"

class MenuScreen : public GameScreen
{
public:
  MenuScreen(ScreenManager* screenManager);
  ~MenuScreen();

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

  Mix_Chunk*     m_MusicPtr;

  Button*        m_NormalButton;
  Button*        m_HardButton;
  Button*        m_ExitButton;
};

