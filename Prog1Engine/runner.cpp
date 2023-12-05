#pragma once
#include "pch.h"
#include "runner.h"
#include <iostream>

#include <chrono>

void Run()
{
	//Main loop flag
	bool running{ true };

	// Set start time
  std::chrono::steady_clock::time_point previousTime{ std::chrono::steady_clock::now() };

	Start();

	//The event loop
	SDL_Event e{};
  float deltaTimeAccumulated{};

	while (running)
	{
		// Poll next event from queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				OnKeyDownEvent(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				OnKeyUpEvent(e.key.keysym.sym);
				break;
			case SDL_MOUSEMOTION:
				OnMouseMotionEvent(e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				OnMouseDownEvent(e.button);
				break;
			case SDL_MOUSEBUTTONUP:
				OnMouseUpEvent(e.button);
				break;
			default:
				break;
			}
		}

		// Get current time
    std::chrono::steady_clock::time_point currentTime{ std::chrono::steady_clock::now() };

		// Calculate elapsed time
		float deltaTime{ std::chrono::duration<float>(currentTime - previousTime).count() };

		// Update current time
		previousTime = currentTime;

		// Prevent jumps in time caused by break points
		if (deltaTime > g_MaxDeltaTime)
		{
			deltaTime = g_MaxDeltaTime;
		}

    // [DYSON] A FixedUpdate implementation, often used for physics
    deltaTimeAccumulated += deltaTime;

    while (deltaTimeAccumulated >= fixedDeltaTime)
    {
      FixedUpdate(fixedDeltaTime);
      deltaTimeAccumulated -= fixedDeltaTime;
    }

		// Call update function, using time in seconds (!)
		Update(deltaTime);

		// Draw in the back buffer
		Draw();
	}
	End();
}