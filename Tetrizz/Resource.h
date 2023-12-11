#pragma once
#include <Core.h>

#ifdef NDEBUG
#define RES(file) (file)
#else
#define RES(file) ("../Resources/" file)
#endif

static const char* FONT_MAIN = RES("dhurjati.otf");

static const char* THEME_MENU = RES("hard.wav");
static const char* THEME_GAME = RES("theme.wav");
static const char* THEME_GAME_OVER = RES("death.wav");

static const char* FX_START = RES("welcome.wav");
static const char* FX_PLACE = RES("place.wav");
static const char* FX_ROTATE = RES("rotate.wav");
static const char* FX_CLEAR_1 = RES("small_rizzler.wav");
static const char* FX_CLEAR_2 = RES("lil_bit_of_rizz.wav");
static const char* FX_CLEAR_3 = RES("you_got_rizz.wav");
static const char* FX_CLEAR_4 = RES("tet_rizz.wav");
static const char* FX_GAME_OVER = RES("game_over.wav");
static const char* FX_SCORE = RES("score.wav");
