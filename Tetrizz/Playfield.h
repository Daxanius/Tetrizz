#pragma once
#include "Core.h"
#include "Tetromino.h"

static const int FIELD_WIDTH{ 10 };
static const int FIELD_HEIGHT{ 24 };

static const float RGB_MAX{ 255.f };
static const int TETRIMINO_COUNT{ 7 }; // For error purposes

// Shapes
static const Point2f L_SHAPE[MINO_COUNT]{ { -1, 0 }, { 0,  0 }, { 1,  0 }, { 2, 0 } };
static const Point2f O_SHAPE[MINO_COUNT]{ { 0,  0 }, { 1,  0 }, { 0,  1 }, { 1, 1 } };
static const Point2f T_SHAPE[MINO_COUNT]{ { 0,  0 }, { 0,  1 }, { -1, 1 }, { 1, 1 } };
static const Point2f J_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 0,  1 }, { 0, 2 } };
static const Point2f S_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 0 }, { 0,  1 }, { 1, 1 } };
static const Point2f Z_SHAPE[MINO_COUNT]{ { 0,  0 }, { -1, 1 }, { 0,  1 }, { 1, 0 } };

static const Tetromino TETRIMINOS_ARR[TETRIMINO_COUNT]{
  Tetromino(L_SHAPE, Color4f{0 / RGB_MAX, 253 / RGB_MAX, 255 / RGB_MAX , 1.0f}),
  Tetromino(O_SHAPE, Color4f{255 / RGB_MAX, 254 / RGB_MAX, 64 / RGB_MAX , 1.0f}),
  Tetromino(T_SHAPE, Color4f{255 / RGB_MAX, 42 / RGB_MAX, 248 / RGB_MAX , 1.0f}),
  Tetromino(J_SHAPE, Color4f{0 / RGB_MAX, 25 / RGB_MAX, 248 / RGB_MAX , 1.0f}),
  Tetromino(J_SHAPE, Color4f{255 / RGB_MAX, 192 / RGB_MAX, 35 / RGB_MAX , 1.0f}),
  Tetromino(S_SHAPE, Color4f{0 / RGB_MAX, 252 / RGB_MAX, 61 / RGB_MAX , 1.0f}),
  Tetromino(Z_SHAPE, Color4f{255 / RGB_MAX, 35 / RGB_MAX, 18 / RGB_MAX , 1.0f})
};

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
  const Tetromino* m_TetriminosArr;   // DO NOT DELETE, array pointer to all predefined tetriminos
  int              m_TetriminosArrSize;

  Color4f*         m_GridArr[FIELD_HEIGHT][FIELD_WIDTH]{nullptr};
  Playstate        m_Playstate{};
  int              m_Score{};

  bool             CanRotate();      // Checks if the Tetromino can rotate
  bool             CanMoveLeft();    // Checks if the tetrmino can move right on the grid
  bool             CanMoveRight();   // Checks if the tetrmino can move left on the grid
  bool             CanMoveDown();    // Checks if the current Tetromino can move down

  void             ClearLines();     // Clears the lines and sets the score
  void             PlaceTetrimino(); // Places the current Tetromino on the grid
public:
  Playfield(const Tetromino tetriminosArr[], int tetrminosArrSize);
  ~Playfield();

  void            MoveLeft();
  void            MoveRight();
  void            MoveDown();         // Moves the tetromino down
  void            Rotate();

  void            SaveTetromino();    // Swaps the current tetrimo with the one storage
  void            QuickPlace();       // Instantly places tetromino

  void            NextTetrimino();

  void            Draw(Point2f position);
  void            Update(float deltaTime);

  Playstate       GetPlaystate() const;
  const int       GetScore() const;
};