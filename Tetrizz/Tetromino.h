#pragma once
#include <Core.h>
#include "GameDefines.h"

static const int  MINO_COUNT{ 4 };

class Tetromino
{
private:
	Color4f  m_MinosColor{};
	Point2f* m_MinosArr;
public:
  Tetromino(const Point2f minosArr[MINO_COUNT], Color4f minosColor);
  Tetromino(const Tetromino &Tetromino);
  ~Tetromino();

	const Point2f* GetMinos() const;
	Color4f        GetColor() const;


	void           Rotate();
  void           Draw(Point2f position);
};