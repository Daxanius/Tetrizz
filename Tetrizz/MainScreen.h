#pragma once
#include "GameScreen.h"

// This manages all the menu screens and plays the audio 
// this way audio is not reset with every menu screen and menu screens are neatly organized
class MainScreen : public GameScreen
{
public:
  MainScreen(ScreenManager* screenManager);
  ~MainScreen();

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
  ScreenManager* m_ParentScreenManager;
  ScreenManager m_ScreenManager;

  Mix_Chunk* m_MusicPtr;
};