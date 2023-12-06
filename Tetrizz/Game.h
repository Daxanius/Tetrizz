#pragma once
#include <Core.h>
#include "Playfield.h"
#include "Tetrimino.h"

#pragma region ownDeclarations
// CONSTANTS
static const float RGB_MAX{ 255.f };

// Shapes
static const Point2f L_SHAPE[]{ { -1, 0 },  { 0,  0 }, { 1,  0 }, { 2, 0 } };
static const Point2f O_SHAPE[]{ { 0,  0 },  { 1,  0 }, { 0,  1 }, { 1, 1 } };
static const Point2f T_SHAPE[]{ { 0,  0 },  { 0,  1 }, { -1, 1 }, { 1, 1 } };
static const Point2f J_SHAPE[]{ { 0,  0 },  { -1, 0 }, { 0,  1 }, { 0, 2 } };
static const Point2f L_SHAPE[]{ { 0,  0 },  { 1,  0 }, { 0,  1 }, { 0, 2 } };
static const Point2f S_SHAPE[]{ { 0,  0 },  { -1, 0 }, { 0,  1 }, { 1, 1 } };
static const Point2f Z_SHAPE[]{ { 0,  0 },  { -1, 1 }, { 0,  1 }, { 1, 0 } };

static const Tetrimino TETRIMINOS_ARR[] {
  Tetrimino(L_SHAPE, Color4f{0   / RGB_MAX, 253 / RGB_MAX, 255 / RGB_MAX}),
  Tetrimino(O_SHAPE, Color4f{255 / RGB_MAX, 254 / RGB_MAX, 64  / RGB_MAX}),
  Tetrimino(T_SHAPE, Color4f{255 / RGB_MAX, 42  / RGB_MAX, 248 / RGB_MAX}),
  Tetrimino(J_SHAPE, Color4f{0   / RGB_MAX, 25  / RGB_MAX, 248 / RGB_MAX}),
  Tetrimino(J_SHAPE, Color4f{255 / RGB_MAX, 192 / RGB_MAX, 35  / RGB_MAX}),
  Tetrimino(S_SHAPE, Color4f{0   / RGB_MAX, 252 / RGB_MAX, 61  / RGB_MAX}),
  Tetrimino(Z_SHAPE, Color4f{255 / RGB_MAX, 35  / RGB_MAX, 18  / RGB_MAX})
};

// GLOBALS
Playfield* m_PlayfieldPtr;
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
