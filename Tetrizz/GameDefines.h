#pragma once
#include <Core.h>

static const int TICKS_PER_SECOND{ 50 };
static const int UPDATES_PER_SECOND{ 1 };
static const int TICKS_PER_UPDATE{ TICKS_PER_SECOND / UPDATES_PER_SECOND };
static const int SPEEDUP_PER_CLEAR{ 1 };
static const int MIN_TICKS_PER_UPDATE{ 2 };

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

static const float TILE_SIZE{ 23.f };
static const int LINE_CLEAR_SCORE{ 300 };

enum Difficulty
{
  Easy,
  Normal,
  Hard
};