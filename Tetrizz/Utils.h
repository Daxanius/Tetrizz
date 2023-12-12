#pragma once
#include <Core.h>

int RandInt(int min, int max);

float RandFloat(float min, float max, int decimals = 2);

void DrawString(const std::string& output, const Point2f topLeft, const int fontSize, const Color4f& color, const std::string& fontLocation);

float Lerp(float start, float end, float t);

Color4f Lerp(const Color4f& start, const Color4f& end, float t);

void Quit();