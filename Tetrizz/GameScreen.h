#pragma once
#include "pch.h"
#include <Core.h>

class GameScreen; // Forward declaration

class ScreenManager
{
public:
  ~ScreenManager();

  void        SetScreen(GameScreen* newScreen);
  GameScreen* GetScreen();
private:
  GameScreen* m_CurrentScreen{ nullptr };
};

// An abstract GameScreen class that all sceens can implement
class GameScreen
{
public:
  // General game functions
  virtual void Draw()                                            = 0;
  virtual void Update(float deltaTime)                           = 0;
  virtual void FixedUpdate(float fixedDeltaTime)                 = 0;

  // Key events
  virtual void OnKeyDownEvent(SDL_Keycode key)                   = 0;
  virtual void OnKeyUpEvent(SDL_Keycode key)                     = 0;
  virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent& e) = 0;
  virtual void OnMouseDownEvent(const SDL_MouseButtonEvent& e)   = 0;
  virtual void OnMouseUpEvent(const SDL_MouseButtonEvent& e)     = 0;
};