#pragma once
#include <Core.h>
#include <vector>
#include "GameDefines.h"
#include "Playfield.h"
#include "Tetromino.h"
#include "Tetrominos.h"
#include "CameraManager.h"
#include "AnimatedText.h";

#pragma region ownDeclarations
struct ScoreText
{
  AnimatedText animatedText;
  int          score;
};

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
Mix_Chunk* g_DeathPtr;
Mix_Chunk* g_ScorePtr;

CameraManager* g_CameraManager;
Playfield* g_PlayfieldPtr;
std::vector<ScoreText> g_ScoreTextEffects;

bool       g_GameOver{};
int        g_TickCount{};

int        g_Score{0};

static const int LINE_CLEAR_SCORE{ 300 };

// Declare your own functions here
void PlaceTetromino();

void DrawSaved(const Point2f& position);
void DrawNext(const Point2f& position);
void AddToScore(int value);

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
