#include "pch.h"
#include "Tetrimino.h"

Tetrimino::Tetrimino(const Point2f minosArr[MINO_COUNT], Color4f minosColor)
{
  m_MinosArr = new Point2f[MINO_COUNT];
  m_MinosColor = minosColor;

  for (int i = 0; i < MINO_COUNT; ++i) {
    m_MinosArr[i] = minosArr[i];
  }
}

Tetrimino::Tetrimino(const Tetrimino &tetrimino)
{
  m_MinosArr = new Point2f[MINO_COUNT];
  m_MinosColor = tetrimino.GetColor();

  for (int i = 0; i < MINO_COUNT; ++i) {
    m_MinosArr[i] = tetrimino.GetMinos()[i];
  }
}

Tetrimino::~Tetrimino()
{
  delete m_MinosArr;
  m_MinosArr = nullptr;
}

const Point2f* Tetrimino::GetMinos() const
{
  return m_MinosArr;
}

Color4f Tetrimino::GetColor() const
{
  return m_MinosColor;
}

void Tetrimino::Rotate()
{

}