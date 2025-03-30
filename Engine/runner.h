// [DYSON] The runner was originally Core, now simplified to one use, running the functions
#pragma once
#include "structs.h"

#pragma region vars

// [DYSON] 
// The maximum amount deltaTime can reach, this is used to prevent
// breakpoints from causing huge jumps in logic. DeltaTime is calculated using system
// time, if you place a breakpoint to debug and continue with the program, deltaTime will be
// a large number, causing huge jumps in logic.
const float g_MaxDeltaTime{ 100 };

/// [DYSON]
/// Defines how many times per second the fixedUpdate function
/// should run.
const float fixedDeltaTime{ 1/50.f };

#pragma endregion vars

// [DYSON] Region moved here from Core.cpp
#pragma region externs

extern void Start();
extern void Update(float deltaTime);

/// [DYSON]
/// An implementation for FixedUpdate, this gets run 50 times each second.
/// It is recommended to use this function for physics and collision calculations.
/// Credits to Dontu Cristian for the implementation
extern void FixedUpdate(float fixedDeltaTime);
extern void Draw();
extern void End();

extern void OnKeyDownEvent(SDL_Keycode key);
extern void OnKeyUpEvent(SDL_Keycode key);
extern void OnMouseMotionEvent(const SDL_MouseMotionEvent& e);
extern void OnMouseDownEvent(const SDL_MouseButtonEvent& e);
extern void OnMouseUpEvent(const SDL_MouseButtonEvent& e);

#pragma endregion externs

/// [DYSON]
/// The runner only runs the given functions
void Run();