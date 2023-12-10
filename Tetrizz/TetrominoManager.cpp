#include "pch.h"
#include "TetrominoManager.h"

TetrominoManager::TetrominoManager(Point2f startPosition, const Tetromino tetrominosArr[], int tetrminosArrSize)
{
  m_TetrominosArr = tetrominosArr;
  m_TetrominosArrSize = tetrminosArrSize;
  m_TetrominoPosition = startPosition;

  NextTetromino();
}

TetrominoManager::~TetrominoManager()
{
  delete m_CurrentTetrominoPtr;
}

void TetrominoManager::SaveTetromino()
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

void TetrominoManager::NextTetromino()
{
  int randomNext{ rand() % m_TetrominosArrSize };

  if (m_QueuedTetrominoIndex < 0) {
    m_QueuedTetrominoIndex = randomNext;
    randomNext = rand() % m_TetrominosArrSize;
  }

  SetCurrentTetromino(m_QueuedTetrominoIndex);
  m_QueuedTetrominoIndex = randomNext;
}

void TetrominoManager::SetCurrentTetromino(int index)
{
  delete m_CurrentTetrominoPtr;
  m_CurrentTetrominoPtr = new Tetromino{ m_TetrominosArr[index] };
  m_CurrentTetrominoIndex = index;
  m_TetrominoPosition = Point2f{ FIELD_WIDTH / 2.f, 0 };
}

int TetrominoManager::GetQueuedTetromino() const
{
  return m_QueuedTetrominoIndex;
}

Point2f TetrominoManager::GetTetrominoPosition() const
{
  return m_TetrominoPosition;
}

void TetrominoManager::SetTetrominoPosition(Point2f position)
{
  m_TetrominoPosition = position;
}

Tetromino* TetrominoManager::GetTetromino() const
{
  return m_CurrentTetrominoPtr;
}

int TetrominoManager::GetTetrominoIndex() const
{
    return m_CurrentTetrominoIndex;
}

int TetrominoManager::GetSavedTetromino() const
{
    return m_SavedTetrominoIndex;
  
}

void TetrominoManager::Reset()
{
    m_CurrentTetrominoPtr = nullptr;
    m_QueuedTetrominoIndex = -1;
    m_SavedTetrominoIndex = -1;
    m_CurrentTetrominoIndex = -1;

    NextTetromino();
}
