#pragma once
#include "pch.h"
#include <Core.h>

class GameScreen; // Forward declaration

class ScreenManager
{
public:
  ~ScreenManager();

  void        SetScreen(GameScreen* newScreen);
  void        SetParent(ScreenManager* parent);

  GameScreen*    GetScreen();
  ScreenManager* GetParent(); // In case you have screenception
private:
  ScreenManager* m_Parent{};
  GameScreen*    m_PreviousScreen{ nullptr };
  GameScreen*    m_CurrentScreen{ nullptr };
};

// An abstract GameScreen class that all sceens can implement
class GameScreen
{
public:
  virtual ~GameScreen() {};

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