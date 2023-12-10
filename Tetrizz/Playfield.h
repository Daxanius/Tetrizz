#pragma once
#include <Core.h>
#include "GameDefines.h"
#include "Tetromino.h"
#include "TetrominoManager.h"

class Playfield
{
public:
  Playfield(const Tetromino tetrominosArr[], int tetrminosArrSize);
  ~Playfield();

  bool            IsTileTaken(int row, int col) const; // Checks if a tile is taken
  bool            CanMove(Point2f direction, int rotations = 0) const; // Checks if the tetrmino can move to a position
  bool            Move(Point2f direction, int rotations = 0); // Moves the tetrimino, returns false if it can't move

  void            SaveTetromino();    // Swaps the current tetrimo with the one storage
  void            QuickPlace();       // Instantly places tetromino

  int             ClearFullLines();   // Clears all full lines, returns the amount cleared
  bool            PlaceTetromino();   // Places the current Tetromino on the grid, returns false if it failed to place
  void            MoveLinesDown();    // Move lines down if possible

  void            NextTetromino();

  void			  ResetBoard();

  void            Draw(Point2f position);
  TetrominoManager* GetState();

  bool            m_CanSaveTetromino{ true };

  Point2f          GetQuickPlacePosition();
private:
  Color4f* m_GridArr[FIELD_HEIGHT][FIELD_WIDTH]{ nullptr };
  TetrominoManager* m_State{};

  void             MoveLineDown(int line);   // Moves a line down
  bool             IsLineFull(int line) const;
  bool             IsLineEmpty(int line) const;
};