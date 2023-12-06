#pragma once
#include "Core.h"
#include "Tetromino.h"

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

struct Playstate
{
  Tetromino* nextTetriminoPtr;    // Will point to the predefined Tetromino array DO NOT DELETE
  Tetromino* savedTetriminoPtr;   // Will point to the predefined Tetromino array DO NOT DELETE
  Tetromino* currentTetriminoPtr; // DO NOT FORGET TO DELETE 
  Point2f    fieldPosition;       // The position of the current Tetromino on the board
};

class Playfield
{
private:
  const Tetromino*  m_TetriminosArr;   // DO NOT DELETE, array pointer to all predefined tetriminos
  int               m_TetriminosArrSize;

  Color4f*          m_GridArr[FIELD_HEIGHT][FIELD_WIDTH]{nullptr};
  Playstate         m_Playstate{};
  int               m_Score{};

  bool              CanRotate();      // Checks if the Tetromino can rotate
  bool              CanMoveLeft();    // Checks if the tetrmino can move right on the grid
  bool              CanMoveRight();   // Checks if the tetrmino can move left on the grid
  bool              CanMoveDown();    // Checks if the current Tetromino can move down

  void              ClearLines();     // Clears the lines and sets the score
  void              PlaceTetrimino(); // Places the current Tetromino on the grid
public:
  Playfield(const Tetromino tetriminosArr[], int tetrminosArrSize);
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