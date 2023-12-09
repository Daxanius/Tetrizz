#pragma once
#include <Core.h>
#include "GameDefines.h"
#include "Tetromino.h"

class FieldState
{
public:
  FieldState(Point2f startPosition, const Tetromino tetrominosArr[], int tetrminosArrSize);
  ~FieldState();

  void       SaveTetromino();    // Swaps the current tetromino with the one storage
  void       NextTetromino();    // Generates the next tetromino
  int        GetQueuedTetromino() const; // Gets the tetromino next in queue

  Point2f    GetTetrominoPosition() const;
  void       SetTetrominoPosition(Point2f position);
  
  Tetromino* GetTetromino();
private:
  const Tetromino* m_TetrominosArr;   // DO NOT DELETE, array pointer to all predefined tetrominos
  int              m_TetrominosArrSize;

  int              m_QueuedTetrominoIndex{ -1 };
  int              m_SavedTetrominoIndex{ -1 };
  int              m_CurrentTetrominoIndex{ -1 };
  Tetromino*       m_CurrentTetrominoPtr{ nullptr };
  Point2f          m_TetrominoPosition;

  void             SetCurrentTetromino(int index);
};