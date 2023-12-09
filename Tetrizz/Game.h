#pragma once
#include <Core.h>
#include "GameDefines.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Tetrominos.h"
#include "CameraManager.h"

#pragma region ownDeclarations
// Variables
Mix_Chunk* g_MusicPtr;
Mix_Chunk* g_WelcomePtr;
Mix_Chunk* g_PlacePtr;
Mix_Chunk* g_ClearPtr;
Mix_Chunk* g_RotatePointer;
Mix_Chunk* g_SmallRizzlerPtr;
Mix_Chunk* g_LilBitOfRizzPtr;
Mix_Chunk* g_YouGotRizzPtr;
Mix_Chunk* g_TetRizzPtr;
Mix_Chunk* g_GameOverPtr;


CameraManager* g_CameraManager;
Playfield* g_PlayfieldPtr;
bool       g_GameOver{};
int        g_TickCount{};

// Declare your own functions here
void PlaceTetromino();

void DrawString(const std::string& output, const Point2f topLeft, const int fontSize, const Color4f& color, const std::string& fontLocation);
void DrawSaved(const Point2f& position);
void DrawNext(const Point2f& position);

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
