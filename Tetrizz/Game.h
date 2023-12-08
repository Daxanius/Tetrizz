#pragma once
#include <Core.h>
#include "Playfield.h"
#include "Tetromino.h"

#pragma region ownDeclarations
// CONSTANTS
static const int TICKS_PER_SECOND{ 50 };
static const int UPDATES_PER_SECOND{ 1 };
static const int TICKS_PER_UPDATE{ int(TICKS_PER_SECOND / UPDATES_PER_SECOND) };


Mix_Chunk* g_MusicPtr;
Playfield* g_PlayfieldPtr;
int g_TickCount{};

// Declare your own functions here
// Texture g_Texture;

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
