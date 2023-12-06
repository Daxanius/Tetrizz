#pragma once

static const int  MINO_COUNT{ 4 };

class Tetrimino
{
private:
	Point2f m_MinosArr[MINO_COUNT];
	Color4f m_MinosColor{};

public:
	Point2f* GetMinos();
	Color4f GetColor();

	void Rotate();

	Tetrimino(Tetrimino* tetrimino);
	Tetrimino(const Point2f minosArr[MINO_COUNT], Color4f minosColor);
	~Tetrimino();
};    

