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
	m_Playstate.fieldPosition.x -= 1;
}

void Playfield::MoveRight()
{
	m_Playstate.fieldPosition.x += 1;
}

void Playfield::MoveDown()
{
	m_Playstate.fieldPosition.y += 1;
}

void  Playfield::Rotate()
{
	if (CanRotate())
	{
		m_Playstate.currentTetriminoPtr->Rotate();
	}
}

void  Playfield::SaveTetromino()
{
	if (m_Playstate.currentTetriminoPtr != nullptr)
	{
		Tetromino* currentPtr{m_Playstate.currentTetriminoPtr};
		Tetromino* SavedPtr{m_Playstate.savedTetriminoPtr};

		m_Playstate.currentTetriminoPtr = SavedPtr;
		m_Playstate.savedTetriminoPtr = currentPtr;
	}
	else
	{
		m_Playstate.savedTetriminoPtr = m_Playstate.currentTetriminoPtr;
		m_Playstate.currentTetriminoPtr = m_Playstate.nextTetriminoPtr;
	}
}

void Playfield::QuickPlace()
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