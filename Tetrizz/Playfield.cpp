#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetromino* tetriminosArr, int tetrminosArrSize)
{
  m_TetriminosArr = tetriminosArr;
  m_TetriminosArrSize = tetrminosArrSize;
}

Playfield::~Playfield()
{
  delete m_Playstate.currentTetriminoPtr;
  m_Playstate.currentTetriminoPtr = nullptr;
}

Playstate Playfield::GetPlaystate() const
{
  return m_Playstate;
}

const int Playfield::GetScore() const
{
  return m_Score;
}

void Playfield::MoveLeft()
{

}

void Playfield::MoveRight()
{

}

void  Playfield::Rotate()
{

}

void  Playfield::SaveTetromino()
{

}

void Playfield::Draw(Point2f position)
{
  // DRAW THE BOARD HERE
}

void Playfield::Update(float deltaTime)
{
  // UPDATE THE BOARD HERE
}