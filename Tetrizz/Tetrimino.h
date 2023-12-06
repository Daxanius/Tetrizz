#pragma once

static const int  MINO_COUNT{ 4 };

class Tetrimino
{
private:
	Point2f* m_MinosArr;
	Color4f  m_MinosColor{};

public:
  Tetrimino(const Point2f minosArr[MINO_COUNT], Color4f minosColor);
  Tetrimino(const Tetrimino &tetrimino);
  ~Tetrimino();

	const Point2f* GetMinos() const;
	Color4f        GetColor() const;

	void           Rotate();
};