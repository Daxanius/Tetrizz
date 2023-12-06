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
      "Project name - Name, firstname - 1DAExx", // title
      0,                                         // Fullscreen mode (SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_FULLSCREEN, 0)
      sizeX,                                     // width
      sizeY,                                     // height
      displayMode.w / 2 - sizeX / 2,             // posX
      displayMode.h / 2 - sizeY / 2,             // posY
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
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();

  // const WindowSettings windowSettings{ GetWindowInfo() };

  //Point2f position{
  //  windowSettings.width  / 2.f - g_Texture.width  / 2.f,
  //  windowSettings.height / 2.f - g_Texture.height / 2.f
  //};

  // const float rotation{ 50.f * sin((g_Pi * 2 / 500.f) * g_TickCount) };
  // DrawTexture(g_Texture, position, Rectf{ 0.0f, 0.0f, g_Texture.width, g_Texture.height }, rotation);

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{
  // process input, do physics 

  //const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
  //if ( pStates[SDL_SCANCODE_RIGHT] )
  //{
  //  MoveCamera(-1.f, 0.f);
  //}

  //if ( pStates[SDL_SCANCODE_LEFT])
  //{
  //  MoveCamera(1.f, 0.f);
  //}

  //if (pStates[SDL_SCANCODE_UP])
  //{
  //  MoveCamera(0.f, 1.f);
  //}

  //if (pStates[SDL_SCANCODE_DOWN])
  //{
  //  MoveCamera(0.f, -1.f);
  //}
}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  ++g_TickCount;
}

void End()
{
	// free game resources here
}
#pragma endregion gameFunctions

//Keyboard and mouse input handling
#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key)
{

}

void OnKeyUpEvent(SDL_Keycode key)
{
	//switch (key)
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
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