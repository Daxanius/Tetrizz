#pragma once
#include "Core.h"
#include "Tetromino.h"

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

static const float TILE_SIZE{ 23.f };

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
  int              m_Score{};

  bool             IsTileTaken(int row, int col) const; // Checks if a tile is taken
  bool             CanRotate();      // Checks if the Tetromino can rotate
  bool             CanMoveLeft();    // Checks if the tetrmino can move right on the grid
  bool             CanMoveRight();   // Checks if the tetrmino can move left on the grid
  bool             CanMoveDown();    // Checks if the current Tetromino can move down

  void             ClearLines();     // Clears the lines and sets the score
  void             PlaceTetromino(); // Places the current Tetromino on the grid

  void             SetCurrentTetrimino(int index);
public:
  Playfield(const Tetromino tetrominosArr[], int tetrminosArrSize);
  ~Playfield();

  void            MoveLeft();
  void            MoveRight();
  void            MoveDown();         // Moves the tetromino down
  void            Rotate();

  void            SaveTetromino();    // Swaps the current tetrimo with the one storage
  void            QuickPlace();       // Instantly places tetromino

  void            NextTetromino();

  void            Draw(Point2f position);
  void            Update();

  Playstate       GetPlaystate() const;
  const int       GetScore() const;
};