#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetromino* tetrominosArr, int tetrminosArrSize)
{
  m_TetrominosArr = tetrominosArr;
  m_TetrominosArrSize = tetrminosArrSize;

  m_Playstate = {
      -1,
      -1,
      -1,
      nullptr,
     { FIELD_WIDTH / 2.f, 0 }
  };

  NextTetromino();
}

Playfield::~Playfield()
{
  delete m_Playstate.currentTetrominoPtr;
  m_Playstate.currentTetrominoPtr = nullptr;
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
	if (CanMoveLeft() == true)
	{
		m_Playstate.fieldPosition.x -= 1;
	}
}

bool Playfield::CanMoveLeft()
{

	for (int i = 0; i < MINO_COUNT; ++i)
	{
		float minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i].x -1 };

    if (m_Playstate.fieldPosition.x + minosPos < 0) {
      return false;
    }
	}

	return true;
}

void Playfield::MoveRight()
{
	if (CanMoveRight())
	{
		m_Playstate.fieldPosition.x += 1;
	}
}

bool Playfield::CanMoveRight()
{
	for (int i = 0; i < MINO_COUNT; ++i)
	{
		float minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i].x +1 };

    if (m_Playstate.fieldPosition.x + minosPos >= FIELD_WIDTH) {
      return false;
    }
	}

	return true;
}

void Playfield::MoveDown()
{
	if (CanMoveDown())
	{
		m_Playstate.fieldPosition.y += 1;
	}
}

bool Playfield::CanMoveDown()
{
	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
		int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x)};
		int gridRow{ int(m_Playstate.fieldPosition.y + minosPos.y) + 1 };

    if (gridRow >= FIELD_HEIGHT || m_GridArr[gridRow][gridColumn] != nullptr) {
      return false;
    }
	}

	return true;
}

void  Playfield::Rotate()
{
	if (CanRotate())
	{
		m_Playstate.currentTetrominoPtr->Rotate();
	}
}

bool Playfield::CanRotate()
{
	return true;
}

void  Playfield::SaveTetromino()
{
	if (m_Playstate.savedTetrominoIndex < 0) {
    m_Playstate.savedTetrominoIndex = m_Playstate.currentTetrominoIndex;
    NextTetromino();
    return;
	}

  int currentIndex{ m_Playstate.currentTetrominoIndex };
  SetCurrentTetrimino(m_Playstate.savedTetrominoIndex);
  m_Playstate.savedTetrominoIndex = currentIndex;
}

void Playfield::QuickPlace()
{

}

void Playfield::PlaceTetromino()
{
	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
		int gridColumn{int( m_Playstate.fieldPosition.x + minosPos.x) };
		int gridRow{int( m_Playstate.fieldPosition.y + minosPos.y) };

		m_GridArr[gridRow][gridColumn] = new Color4f{ m_Playstate.currentTetrominoPtr->GetColor() };
	}

	NextTetromino();
}

void Playfield::SetCurrentTetrimino(int index)
{
  delete m_Playstate.currentTetrominoPtr;
  m_Playstate.currentTetrominoPtr = new Tetromino{ m_TetrominosArr[index] };
  m_Playstate.currentTetrominoIndex = m_Playstate.nextTetrominoIndex;
  m_Playstate.fieldPosition = Point2f{ FIELD_WIDTH / 2.f, 0 };
}

void Playfield::NextTetromino()
{
  int randomNext{ rand() % m_TetrominosArrSize };

  if (m_Playstate.nextTetrominoIndex < 0) {
    m_Playstate.nextTetrominoIndex = randomNext;
    randomNext = rand() % m_TetrominosArrSize;
  }

  SetCurrentTetrimino(m_Playstate.nextTetrominoIndex);
  m_Playstate.nextTetrominoIndex = randomNext;
}

void Playfield::Draw(Point2f position)
{
	for (int colIndex = 0; colIndex < FIELD_WIDTH; ++colIndex)
	{
		for (int rowIndex = 0; rowIndex < FIELD_HEIGHT; ++rowIndex)
		{			
			Rectf sourceRect{};
			sourceRect.height = TILE_SIZE;
			sourceRect.width = TILE_SIZE;
			sourceRect.left = position.x + TILE_SIZE * colIndex;
			sourceRect.top = position.y + TILE_SIZE * rowIndex;

      SetColor(0, 0, 0);
      if (m_GridArr[rowIndex][colIndex] != nullptr) {
        SetColor(*m_GridArr[rowIndex][colIndex]);
      }

			FillRect(sourceRect);
			SetColor(1.0f, 1.0f, 1.0f);
			DrawRect(sourceRect);
		}
	}

	
	const Point2f tetrominoPosition{ m_Playstate.fieldPosition };

	for (int minoIndex = 0; minoIndex < MINO_COUNT; ++minoIndex)
	{
		Point2f mino = m_Playstate.currentTetrominoPtr->GetMinos()[minoIndex];

		Rectf sourceRect{};
		sourceRect.height = TILE_SIZE;
		sourceRect.width = TILE_SIZE;
		sourceRect.left = position.x + TILE_SIZE * (tetrominoPosition.x + mino.x) ;
		sourceRect.top = position.y + TILE_SIZE * (tetrominoPosition.y + mino.y);

		SetColor(m_Playstate.currentTetrominoPtr->GetColor());
		FillRect(sourceRect);
		SetColor(1.0f, 1.0f, 1.0f);
		DrawRect(sourceRect);
	}

  // DRAW THE BOARD HERE
}

void Playfield::Update()
{
	if (!CanMoveDown())
	{
    PlaceTetromino();
	}	
	
  MoveDown();
}