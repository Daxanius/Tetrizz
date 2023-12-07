#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions
void Start()
{
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
  g_PlayfieldPtr = new Playfield(TETRIMINOS_ARR, TETRIMINO_COUNT);
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();

  // const WindowSettings windowSettings{ GetWindowInfo() };
  g_PlayfieldPtr->Draw({TILE_X_OFFSET, TILE_Y_OFFSET});

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{
  if (g_TickCount % TICKS_PER_UPDATE == 0) {
    g_PlayfieldPtr->Update(deltaTime);
  }
}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  ++g_TickCount;
}

void End()
{
	// free game resources here
  delete g_PlayfieldPtr;
  g_PlayfieldPtr = nullptr;
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{
  switch (key)
  {
  case SDLK_LEFT:
    g_PlayfieldPtr->MoveLeft();
	  break;
  case SDLK_RIGHT:
    g_PlayfieldPtr->MoveRight();
	  break;
  case SDLK_UP:
    g_PlayfieldPtr->Rotate();
  case SDLK_DOWN:
    g_PlayfieldPtr->MoveDown();
    break;
  case SDLK_SPACE:
    g_PlayfieldPtr->QuickPlace();
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
// Define your own functions here

#pragma endregion ownDefinitions