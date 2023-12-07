#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetromino* tetriminosArr, int tetrminosArrSize)
{
  m_TetriminosArr = tetriminosArr;
  m_TetriminosArrSize = tetrminosArrSize;

  m_Playstate.currentTetriminoPtr = new Tetromino(TETRIMINOS_ARR[0]) ;
  m_Playstate.fieldPosition = { 0, 0 };
  m_Playstate.nextTetriminoPtr = nullptr;
  m_Playstate.savedTetriminoPtr = nullptr;

}

Playfield::~Playfield()
{
  delete m_Playstate.currentTetriminoPtr;
  m_Playstate.currentTetriminoPtr = nullptr;
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
	if (CanMoveLeft())
	{
		m_Playstate.fieldPosition.x -= 1;
	}
}

bool Playfield::CanMoveLeft()
{
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
	return true;
}

void  Playfield::Rotate()
{
	if (CanRotate())
	{
		m_Playstate.currentTetriminoPtr->Rotate();
	}
}

bool Playfield::CanRotate()
{
	return true;
}

void  Playfield::SaveTetromino()
{
	if (m_Playstate.currentTetriminoPtr != nullptr)
	{
		Tetromino* currentPtr{m_Playstate.currentTetriminoPtr};
		Tetromino* SavedPtr{m_Playstate.savedTetriminoPtr};

		m_Playstate.currentTetriminoPtr = SavedPtr;
		m_Playstate.savedTetriminoPtr = currentPtr;
	}
	else
	{
		m_Playstate.savedTetriminoPtr = m_Playstate.currentTetriminoPtr;
		m_Playstate.currentTetriminoPtr = m_Playstate.nextTetriminoPtr;
	}
}

void Playfield::QuickPlace()
{

}

void Playfield::Draw(Point2f position)
{
	static const float TILE_SIZE{ 20.f };



	for (int colIndex{}; colIndex < FIELD_WIDTH; colIndex++)
	{
		for (int rowIndex{}; rowIndex < FIELD_HEIGHT; rowIndex++)
		{			
			Rectf sourceRect{};
			sourceRect.height = TILE_SIZE;
			sourceRect.width = TILE_SIZE;
			sourceRect.left = position.x + TILE_SIZE * colIndex;
			sourceRect.top = position.y + TILE_SIZE * rowIndex;

			SetColor(0, 0, 0);
			FillRect(sourceRect);
			SetColor(1.0f, 1.0f, 1.0f);
			DrawRect(sourceRect);
		}
	}

	
	const Point2f tetriminoPosition{ m_Playstate.fieldPosition };

	for (int minoIndex{}; minoIndex < MINO_COUNT; minoIndex++)
	{
		Point2f mino = m_Playstate.currentTetriminoPtr->GetMinos()[minoIndex];

		Rectf sourceRect{};
		sourceRect.height = TILE_SIZE;
		sourceRect.width = TILE_SIZE;
		sourceRect.left = position.x + TILE_SIZE * (tetriminoPosition.x + mino.x) ;
		sourceRect.top = position.y + TILE_SIZE * (tetriminoPosition.y + mino.y);

		SetColor(m_Playstate.currentTetriminoPtr->GetColor());
		FillRect(sourceRect);
		SetColor(1.0f, 1.0f, 1.0f);
		DrawRect(sourceRect);
	}

  // DRAW THE BOARD HERE
}

void Playfield::Update(float deltaTime)
{
  // UPDATE THE BOARD HERE
}