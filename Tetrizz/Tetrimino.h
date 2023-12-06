#pragma once

class Tetrimino
{
private:
	static const int  MINOS_COUNT{4};
	Point2f m_MinosArr[MINOS_COUNT];
	Color4f m_MinosColor{};

public:
	Point2f* GetMinos();
	Color4f GetColor();
	int GetMinosCount();

	void Rotate();

	Tetrimino(Tetrimino* tetrimino);
	Tetrimino(const Point2f minosArr[MINOS_COUNT], Color4f minosColor);
	~Tetrimino();
};    