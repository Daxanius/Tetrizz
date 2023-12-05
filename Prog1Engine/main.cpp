// precompiled header file
#include "pch.h"
#include <iostream>
#include "runner.h"
#include "Core.h"

static void PrintCredits()
{
  std::cout
    << "[The Dyson Project]\n"
    << "The Programming 1 engine modified by and for students\n"
    << "Credits:\n\n"
    << "- Lies Pinket (original engine, probably)\n"
    << "- Balder Huybreghs (random student or something)\n"
    << "- Dontu Cristian (proud writer of fixedUpdate)\n"
    << "- Thomas (couldn't open the door)\n\n"
    << "!! Use this engine at your own risk !!\n"
  ;
}

int main(int argc, char* args[])
{
  // [DYSON] Please do not remove or modify this line / function
  PrintCredits();

	// seed the pseudo random number generator
	srand(unsigned int(time(nullptr)));

	// Initialize SDL and OpenGL in core.cpp with the given window settings
	Initialize();

	// Event loop
	Run();

	// Clean up SDL and OpenGL in core.cpp
	Cleanup();

	return 0;
}