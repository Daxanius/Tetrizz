#include "pch.h"
#include "Tetromino.h"

Tetromino::Tetromino(const Point2f minosArr[MINO_COUNT], Color4f minosColor)
{
  m_MinosArr = new Point2f[MINO_COUNT];
  m_MinosColor = minosColor;

  for (int i = 0; i < MINO_COUNT; ++i) {
    m_MinosArr[i] = minosArr[i];
  }
}

Tetromino::Tetromino(const Tetromino &Tetromino)
{
  m_MinosArr = new Point2f[MINO_COUNT];
  m_MinosColor = Tetromino.GetColor();

  for (int i = 0; i < MINO_COUNT; ++i) {
    m_MinosArr[i] = Tetromino.GetMinos()[i];
  }
}

Tetromino::~Tetromino()
{
  delete m_MinosArr;
  m_MinosArr = nullptr;
}

const Point2f* Tetromino::GetMinos() const
{
  return m_MinosArr;
}

Color4f Tetromino::GetColor() const
{
  return m_MinosColor;
}

void Tetromino::Rotate()
{
    for (int i = 0; i < MINO_COUNT; ++i) {
      m_MinosArr[i] = { -m_MinosArr[i].y,  m_MinosArr[i].x };
    }
}