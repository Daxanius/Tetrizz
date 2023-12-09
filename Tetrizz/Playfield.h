#pragma once
#include <Core.h>
#include "GameDefines.h"
#include "Tetromino.h"

struct Playstate
{
	int        nextTetrominoIndex;
  int        savedTetrominoIndex;
  int        currentTetrominoIndex;
  Tetromino* currentTetrominoPtr; // DO NOT FORGET TO DELETE 
  Point2f    fieldPosition;       // The position of the current Tetromino on the board
};

class Playfield
{
private:
  const Tetromino* m_TetrominosArr;   // DO NOT DELETE, array pointer to all predefined tetrominos
  int              m_TetrominosArrSize;

  Color4f*         m_GridArr[FIELD_HEIGHT][FIELD_WIDTH]{nullptr};
  Playstate        m_Playstate{};

  void             MoveLineDown(int line);   // Moves a line down
  bool             IsLineFull(int line) const;
  bool             IsLineEmpty(int line) const;
  
  void             SetCurrentTetrimino(int index);
public:
  Playfield(const Tetromino tetrominosArr[], int tetrminosArrSize);
  ~Playfield();

  bool            IsTileTaken(int row, int col) const; // Checks if a tile is taken
  bool            CanMove(Point2f direction, int rotations = 0) const; // Checks if the tetrmino can move to a position
  bool            Move(Point2f direction, int rotations = 0); // Moves the tetrimino, returns false if it can't move

  void            SaveTetromino();    // Swaps the current tetrimo with the one storage
  void            QuickPlace();       // Instantly places tetromino

  int             ClearFullLines();   // Clears all full lines, returns the amount cleared
  void            PlaceTetromino();   // Places the current Tetromino on the grid
  void            MoveLinesDown();    // Move lines down if possible

  void            NextTetromino();

  void            Draw(Point2f position);

  Playstate       GetPlaystate() const;
};