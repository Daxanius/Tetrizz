#pragma once
//ML Detection Extension
#ifdef _DEBUG
#define _CRTDBm_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DEBUm_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUm_NEW
#endif
// SDL and OpenGL Includes
#pragma warning(disable : 26812)
#pragma warning(disable : 4820)
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h> 
#include <SDL_image.h>

#pragma warning(default : 26812)
#include "structs.h"