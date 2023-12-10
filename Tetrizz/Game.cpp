#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions
void Start()
{
  g_ScreenManagerPtr = new ScreenManager();
  GameScreen* screen{ new MenuScreen(g_ScreenManagerPtr) };
  g_ScreenManagerPtr->SetScreen(screen);

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
}

void End()
{
  delete g_ScreenManagerPtr;
  Mix_CloseAudio();
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();

  g_ScreenManagerPtr->GetScreen()->Draw();

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{
  g_ScreenManagerPtr->GetScreen()->Update(deltaTime);
}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  g_ScreenManagerPtr->GetScreen()->FixedUpdate(fixedDeltaTime);
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
  g_ScreenManagerPtr->GetScreen()->OnKeyDownEvent(key);
}

void OnKeyUpEvent(SDL_Keycode key)
{
  g_ScreenManagerPtr->GetScreen()->OnKeyUpEvent(key);
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  g_ScreenManagerPtr->GetScreen()->OnMouseMotionEvent(e);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  g_ScreenManagerPtr->GetScreen()->OnMouseDownEvent(e);
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  g_ScreenManagerPtr->GetScreen()->OnMouseUpEvent(e);
}
#pragma endregion inputHandling

#pragma region ownDefinitions

#pragma endregion ownDefinitions