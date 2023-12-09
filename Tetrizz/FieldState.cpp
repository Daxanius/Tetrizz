#include "pch.h"
#include "FieldState.h"

FieldState::FieldState(Point2f startPosition, const Tetromino tetrominosArr[], int tetrminosArrSize)
{
  m_TetrominosArr = tetrominosArr;
  m_TetrominosArrSize = tetrminosArrSize;
  m_TetrominoPosition = startPosition;

  NextTetromino();
}

FieldState::~FieldState()
{
  delete m_CurrentTetrominoPtr;
}

void FieldState::SaveTetromino()
{
  if (m_SavedTetrominoIndex < 0) {
    m_SavedTetrominoIndex = m_CurrentTetrominoIndex;
    NextTetromino();
    return;
  }

  int currentIndex{ m_CurrentTetrominoIndex };
  SetCurrentTetromino(m_SavedTetrominoIndex);
  m_SavedTetrominoIndex = currentIndex;
}

void FieldState::NextTetromino()
{
  int randomNext{ rand() % m_TetrominosArrSize };

  if (m_QueuedTetrominoIndex < 0) {
    m_QueuedTetrominoIndex = randomNext;
    randomNext = rand() % m_TetrominosArrSize;
  }

  SetCurrentTetromino(m_QueuedTetrominoIndex);
  m_QueuedTetrominoIndex = randomNext;
}

void FieldState::SetCurrentTetromino(int index)
{
  delete m_CurrentTetrominoPtr;
  m_CurrentTetrominoPtr = new Tetromino{ m_TetrominosArr[index] };
  m_CurrentTetrominoIndex = index;
  m_TetrominoPosition = Point2f{ FIELD_WIDTH / 2.f, 0 };
}

int FieldState::GetQueuedTetromino() const
{
  return m_QueuedTetrominoIndex;
}

Point2f FieldState::GetTetrominoPosition() const
{
  return m_TetrominoPosition;
}

void FieldState::SetTetrominoPosition(Point2f position)
{
  m_TetrominoPosition = position;
}

Tetromino* FieldState::GetTetromino()
{
  return m_CurrentTetrominoPtr;
}
