#pragma once
#include <Core.h>
#include "GameDefines.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Tetrominos.h"

#pragma region ownDeclarations
// Variables
Mix_Chunk* g_MusicPtr;
Mix_Chunk* g_WelcomePtr;

Playfield* g_PlayfieldPtr;
int g_TickCount{};

// Declare your own functions here

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
