#include "pch.h"
#include "Game.h"
#include <iostream>
#include "MainScreen.h"
#include "Utils.h"

//Basic game functions
#pragma region gameFunctions
void Start()
{
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) < 0) {
    Quit();
  }

  SDL_DisplayMode displayMode{ GetDisplayMode() };
  const float sizeX{ 800.f };
  const float sizeY{ 600.f };

  WindowSettings window;

#ifdef NDEBUG  // NDEBUG is defined in Release builds
  window = WindowSettings{
      "Tetrizz - Balder Huybreghs & Quentin Demuynck - 1DAE16", // title
      SDL_WINDOW_FULLSCREEN,                     // Fullscreen mode
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

#else
  window = WindowSettings{
      "Tetrizz - Balder Huybreghs & Quentin Demuynck - 1DAE16", // title
      0,                                        // Windowed mode
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
#endif

  // [DYSON] Creates a window, you can call this as many times as you want
  // to create a bunch of windows, just make sure to use SelectWindow(int id) to
  // select the window to update and draw to. 
  // This function returns the int id of the window created
  MakeWindow(window);

  g_ScreenManager = ScreenManager();
  GameScreen* screen{ new MainScreen(&g_ScreenManager) };
  g_ScreenManager.SetScreen(screen);
}

void End()
{
  Mix_CloseAudio();
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();

  g_ScreenManager.GetScreen()->Draw();

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{
  g_ScreenManager.GetScreen()->Update(deltaTime);
}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  //g_ScreenManager.Update();
  g_ScreenManager.GetScreen()->FixedUpdate(fixedDeltaTime);
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
  g_ScreenManager.GetScreen()->OnKeyDownEvent(key);
}

void OnKeyUpEvent(SDL_Keycode key)
{
  g_ScreenManager.GetScreen()->OnKeyUpEvent(key);
}

void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  g_ScreenManager.GetScreen()->OnMouseMotionEvent(e);
}

void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  g_ScreenManager.GetScreen()->OnMouseDownEvent(e);
}

void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  g_ScreenManager.GetScreen()->OnMouseUpEvent(e);
}
#pragma endregion inputHandling

#pragma region ownDefinitions

#pragma endregion ownDefinitions