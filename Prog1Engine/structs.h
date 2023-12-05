// [DYSON] This file has been modified for clarity, it's .cpp variant has been removed
#pragma once
#include <string>

/// [DYSON] Added extra window configuration settings
struct WindowSettings
{
	std::string title;
  Uint32 fullscreenFlags;
	float width;
	float height;
  int posX;
  int posY;
  float opacity;
	bool vsync;
  bool lineSmoothing;
  bool alwaysOnTop;
  bool bordered;
};

struct Point2f
{
	float x;
	float y;
};

struct Rectf
{
	float left;
	float top;
	float width;
	float height;
};

struct Color4f
{
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Point2f center;
	float radius;
};

struct Ellipsef
{
	Point2f center;
	float radiusX;
	float radiusY;
};
