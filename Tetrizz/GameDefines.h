#pragma once
#include <Core.h>

static const int TICKS_PER_SECOND{ 50 };
static const int UPDATES_PER_SECOND{ 2 };
static const int TICKS_PER_UPDATE{ int(TICKS_PER_SECOND / UPDATES_PER_SECOND) };

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

static const float TILE_SIZE{ 23.f };
static const int LINE_CLEAR_SCORE{ 300 };