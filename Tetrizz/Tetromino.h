#pragma once
#include "Core.h"

static const int  MINO_COUNT{ 4 };

class Tetromino
{
private:
	Point2f* m_MinosArr;
	Color4f  m_MinosColor{};

public:
  Tetromino(const Point2f minosArr[MINO_COUNT], Color4f minosColor);
  Tetromino(const Tetromino &Tetromino);
  ~Tetromino();

	const Point2f* GetMinos() const;
	Color4f        GetColor() const;

	void           Rotate();
};