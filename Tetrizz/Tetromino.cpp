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
  delete[] m_MinosArr;
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

void Tetromino::Draw(Point2f position, float opacity)
{
  for (int minoIndex = 0; minoIndex < MINO_COUNT; ++minoIndex)
  {
    Point2f mino{ m_MinosArr[minoIndex] };

    Rectf sourceRect{
      position.x + TILE_SIZE * mino.x,
      position.y + TILE_SIZE * mino.y,
      TILE_SIZE,
      TILE_SIZE
    };

    Color4f color{ GetColor() };
    color.a = opacity;

    SetColor(color);
    FillRect(sourceRect);
    SetColor(1.0f, 1.0f, 1.0f);
    DrawRect(sourceRect);
  }
}

