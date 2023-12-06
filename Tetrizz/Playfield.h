#pragma once
#include "Core.h"
#include "Game.h"
#include "Tetrimino.h"

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

struct Playstate
{
  Tetrimino* nextTetriminoPtr;    // Will point to the predefined tetrimino array DO NOT DELETE
  Tetrimino* savedTetriminoPtr;   // Will point to the predefined tetrimino array DO NOT DELETE
  Tetrimino* currentTetriminoPtr; // DO NOT FORGET TO DELETE 
  Point2f    fieldPosition;       // The position of the current tetrimino on the board
};

class Playfield
{
private:
  const Tetrimino*  m_TetriminosArr;   // DO NOT DELETE, array pointer to all predefined tetriminos
  int               m_TetriminosArrSize;

  Color4f*          m_GridArr[FIELD_HEIGHT][FIELD_WIDTH]{nullptr};
  Playstate         m_Playstate{};
  int               m_Score{};

  bool              CanRotate();      // Checks if the tetrimino can rotate
  bool              CanMoveLeft();    // Checks if the tetrmino can move right on the grid
  bool              CanMoveRight();   // Checks if the tetrmino can move left on the grid
  bool              CanMoveDown();    // Checks if the current tetrimino can move down

  void              ClearLines();     // Clears the lines and sets the score
  void              PlaceTetrimino(); // Places the current tetrimino on the grid
public:
  Playfield(const Tetrimino tetriminosArr[], int tetrminosArrSize);
  ~Playfield();

  void              MoveLeft();
  void              MoveRight();
  void              Rotate();
  void              SaveTetrimo();    // Swaps the current tetrimo with the one storage

  void              NextTetrimino();

  void              Draw(Point2f position);
  void              Update(float deltaTime);

  Playstate         GetPlaystate() const;
  const int         GetScore() const;
};