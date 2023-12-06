#pragma once
#include <Core.h>
#include "Playfield.h"
#include "Tetrimino.h"



#pragma region ownDeclarations
// Constants


Playfield* m_PlayfieldPtr;
static const Point2f L_SHAPE[4]{ {-1 , 0 } , { 0 , 0 } , { 1 , 0 } , { 2 ,0 } };
static const Tetrimino TETRIMINOS_ARR[] {Tetrimino(L_SHAPE , Color4f{0.2f ,0.5f,0.9f} ) } ;

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
