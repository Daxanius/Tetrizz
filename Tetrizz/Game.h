#pragma once
#include <Core.h>

#pragma region ownDeclarations
// Declare your own global variables here

// Declare your own functions here
// Texture g_Texture;
int g_TickCount{};

#pragma endregion ownDeclarations

#pragma region gameFunctions
void Start();
void Draw();
void Update(float deltaTime);
void FixedUpdate(float fixedDeltaTime);
void End();
#pragma endregion gameFunctions

#pragma region inputHandling											
void OnKeyDownEvent(SDL_Keycode key);
void OnKeyUpEvent(SDL_Keycode key);
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
#pragma endregion inputHandling
