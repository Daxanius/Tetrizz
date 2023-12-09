#include "pch.h"
#include "Game.h"
#include <iostream>

//Basic game functions
#pragma region gameFunctions
void Start()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL Mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
		SDL_Quit(); // Quit SDL if Mixer initialization fails
	}

	g_MusicPtr = Mix_LoadWAV("../Resources/korobeiniki.wav");
  if (g_MusicPtr == nullptr) {
    std::cerr << "Failed to load sound! Mix_Error: " << Mix_GetError() << std::endl;
    SDL_Quit();
  }

  g_WelcomePtr = Mix_LoadWAV("../Resources/welcome.wav");
  if (g_WelcomePtr == nullptr) {
	  std::cerr << "Failed to load sound! Mix_Error: " << Mix_GetError() << std::endl;
	  SDL_Quit();
  }

  Mix_PlayChannel(0, g_WelcomePtr, 0);
  Mix_PlayChannel(-1, g_MusicPtr, -1);

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
  g_PlayfieldPtr = new Playfield(TETROMINOS_ARR, TETROMINO_COUNT);
}

// Put your own draw statements here
void Draw()
{
  // [DYSON] Clears the background of the current window
	ClearBackground();

	DrawString("Hello World", { 10 , 10 }, 20, { 1.0 ,1.0 ,1.0 ,1.0 }, "Resources/spritz.otf");

  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  const float boardWidthOffset = (TILE_SIZE * FIELD_WIDTH) / 2.f;
  const float boardHeightOffset = (TILE_SIZE * FIELD_HEIGHT) / 2.f;

  g_PlayfieldPtr->Draw( { centerX - boardWidthOffset, centerY - boardHeightOffset } );

  // [DYSON] Repaints on the current window
  DrawWindow();
}

void Update(float deltaTime)
{

}

// [DYSON] Gets executed 50x per second
void FixedUpdate(float fixedDeltaTime)
{
  if (g_TickCount % TICKS_PER_UPDATE == 0) {
    g_PlayfieldPtr->Update();
  }

  ++g_TickCount;
}

void End()
{
	// free game resources here
  delete g_PlayfieldPtr;
  g_PlayfieldPtr = nullptr;
  Mix_CloseAudio;
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

void DrawString(const std::string& output , const Point2f topLeft, const int fontSize, const Color4f& color, const std::string& fontLocation)
{
	Texture texturePtr;
	TextureFromString(output, fontLocation, fontSize, color, texturePtr);
	DrawTexture(texturePtr, topLeft);
}

#pragma endregion ownDefinitions