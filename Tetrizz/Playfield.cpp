#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetrimino* tetriminosArr, int tetrminosArrSize)
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