#pragma once
#include <Core.h>
#include "Playfield.h"
#include "Tetromino.h"

#pragma region ownDeclarations
// CONSTANTS
static const float RGB_MAX{ 255.f };
static const int TETRIMINO_COUNT{ 7 }; // For error purposes

// Shapes
static const Point2f L_SHAPE[MINO_COUNT]{ { -1, 0 }, { 0,  0 }, { 1,  0 }, { 2, 0 } };
static const Point2f O_SHAPE[MINO_COUNT]{ { 0,  0 }, { 1,  0 }, { 0,  1 }, { 1, 1 } };
static const Point2f T_SHAPE[MINO_COUNT]{ { 0,  0 }, { 0,  1 }, { -1, 1 }, { 1, 1 } };
static const Point2f J_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 0,  1 }, { 0, 2 } };
static const Point2f L_SHAPE[MINO_COUNT]{ { 0,  0 }, { 1,  0 }, { 0,  1 }, { 0, 2 } };
static const Point2f S_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 0,  1 }, { 1, 1 } };
static const Point2f Z_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 1 }, { 0,  1 }, { 1, 0 } };

static const Tetromino TETRIMINOS_ARR[TETRIMINO_COUNT] {
  Tetromino(L_SHAPE, Color4f{0   / RGB_MAX, 253 / RGB_MAX, 255 / RGB_MAX}),
  Tetromino(O_SHAPE, Color4f{255 / RGB_MAX, 254 / RGB_MAX, 64  / RGB_MAX}),
  Tetromino(T_SHAPE, Color4f{255 / RGB_MAX, 42  / RGB_MAX, 248 / RGB_MAX}),
  Tetromino(J_SHAPE, Color4f{0   / RGB_MAX, 25  / RGB_MAX, 248 / RGB_MAX}),
  Tetromino(J_SHAPE, Color4f{255 / RGB_MAX, 192 / RGB_MAX, 35  / RGB_MAX}),
  Tetromino(S_SHAPE, Color4f{0   / RGB_MAX, 252 / RGB_MAX, 61  / RGB_MAX}),
  Tetromino(Z_SHAPE, Color4f{255 / RGB_MAX, 35  / RGB_MAX, 18  / RGB_MAX})
};


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
