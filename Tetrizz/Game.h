#pragma once
#include <Core.h>
#include "Playfield.h"
#include "Tetromino.h"

#pragma region ownDeclarations
// CONSTANTS
static const int TICKS_PER_SECOND{ 50 };
static const int UPDATES_PER_SECOND{ 1 };
static const int TICKS_PER_UPDATE{ int(TICKS_PER_SECOND / UPDATES_PER_SECOND) };

// Tetromino related stuff
static const float RGB_MAX{ 255.f };
static const int TETROMINO_COUNT{ 7 }; // For error purposes

static const Point2f I_SHAPE[MINO_COUNT]{ { -1, 0 }, { 0,  0 }, { 1,  0 }, { 2, 0 } };
static const Point2f O_SHAPE[MINO_COUNT]{ { 0,  0 }, { 1,  0 }, { 0,  1 }, { 1, 1 } };
static const Point2f T_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 1,  0 }, { 0, 1 } };
static const Point2f J_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 1,  0 }, { 1, 1 } };
static const Point2f L_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 1,  0 }, { -1, 1 } };
static const Point2f S_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 0,  1 }, { 1, 1 } };
static const Point2f Z_SHAPE[MINO_COUNT]{ { 0,  0 }, { 1,  0 }, { 0,  1 }, { -1, 1 } };


static const Tetromino TETROMINOS_ARR[TETROMINO_COUNT]{
  Tetromino(I_SHAPE, Color4f{0 / RGB_MAX, 253 / RGB_MAX, 255 / RGB_MAX , 1.0f}),
  Tetromino(O_SHAPE, Color4f{255 / RGB_MAX, 254 / RGB_MAX, 64 / RGB_MAX , 1.0f}),
  Tetromino(T_SHAPE, Color4f{255 / RGB_MAX, 42 / RGB_MAX, 248 / RGB_MAX , 1.0f}),
  Tetromino(J_SHAPE, Color4f{0 / RGB_MAX, 25 / RGB_MAX, 248 / RGB_MAX , 1.0f}),
  Tetromino(L_SHAPE, Color4f{255 / RGB_MAX, 192 / RGB_MAX, 35 / RGB_MAX , 1.0f}),
  Tetromino(S_SHAPE, Color4f{0 / RGB_MAX, 252 / RGB_MAX, 61 / RGB_MAX , 1.0f}),
  Tetromino(Z_SHAPE, Color4f{255 / RGB_MAX, 35 / RGB_MAX, 18 / RGB_MAX , 1.0f})
};

// Variables
Mix_Chunk* g_MusicPtr;
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
