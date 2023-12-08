#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetromino* tetrominosArr, int tetrminosArrSize)
{
  m_TetrominosArr = tetrominosArr;
  m_TetrominosArrSize = tetrminosArrSize;

  m_RotateSoundPtr = Mix_LoadWAV("../Resources/rotate.wav");
  m_PlaceSoundPtr = Mix_LoadWAV("../Resources/place.wav");
  m_TickSoundPtr = Mix_LoadWAV("../Resources/tick.wav");

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

  delete m_RotateSoundPtr;
  delete m_PlaceSoundPtr;
  delete m_TickSoundPtr;
}

Playstate Playfield::GetPlaystate() const
{
  return m_Playstate;
}

bool Playfield::CheckLine(int line)
{
	for (float index{}; index < FIELD_WIDTH; index++)
	{
		Point2f gridSpace{ index , float(line) };
		if (m_GridArr[int(gridSpace.y)][int(gridSpace.x)] == nullptr)
		{
			return false;
		}
	}

	return true;
}

void Playfield::ClearLines()
{
	for (int lineHeightIndex{ FIELD_HEIGHT - 1 }; lineHeightIndex >= 0; lineHeightIndex--)
	{
		if (CheckLine(lineHeightIndex))
		{
			for (int lineWidthIndex{}; lineWidthIndex < FIELD_WIDTH; lineWidthIndex++)
			{
				m_GridArr[lineHeightIndex][lineWidthIndex] = nullptr;
			}

			for (int index{ lineHeightIndex - 1 }; index >= 0; index--)
			{
				for (int lineWidthIndex{}; lineWidthIndex < FIELD_WIDTH; lineWidthIndex++)
				{
					m_GridArr[index + 1][lineWidthIndex] = m_GridArr[index][lineWidthIndex];

				}
			}
		}
	}
}


const int Playfield::GetScore() const
{
  return m_Score;
}

bool Playfield::IsTileTaken(int row, int col) const
{
  return col < 0 || col >= FIELD_WIDTH || row >= FIELD_HEIGHT || row < 0 || m_GridArr[row][col] != nullptr;
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
    Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
    int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x) -1 };
    int gridRow{ int(m_Playstate.fieldPosition.y + minosPos.y) };

    if (IsTileTaken(gridRow, gridColumn)) {
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
    Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
    int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x) +1 };
    int gridRow{ int(m_Playstate.fieldPosition.y + minosPos.y) };

    if (IsTileTaken(gridRow, gridColumn)) {
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
    Mix_PlayChannel(-1, m_TickSoundPtr, 0);
	}
}

bool Playfield::CanMoveDown()
{
	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
		int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x)};
		int gridRow{ int(m_Playstate.fieldPosition.y + minosPos.y) + 1 };

    if (IsTileTaken(gridRow, gridColumn)) {
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
    Mix_PlayChannel(-1, m_RotateSoundPtr, 0);
	}
}

bool Playfield::CanRotate()
{
  Tetromino* t = new Tetromino(*m_Playstate.currentTetrominoPtr);
  t->Rotate();

  for (int i = 0; i < MINO_COUNT; ++i)
  {
    Point2f minosPos{ t->GetMinos()[i] };
    int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x) };
    int gridRow{ int(m_Playstate.fieldPosition.y + minosPos.y) };

    if (IsTileTaken(gridRow, gridColumn)) {
      delete t;
      return false;
    }
  }

  delete t;
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

	
	int gridColumn{ int(m_Playstate.fieldPosition.x) };
	int gridRow{ int(m_Playstate.fieldPosition.y) };

	bool foundPosition{};
	while (gridRow < FIELD_HEIGHT && !foundPosition)
	{
		for (int i = 0; i < MINO_COUNT; ++i)
		{
			Point2f minosPos{ m_Playstate.currentTetrominoPtr->GetMinos()[i] };
			int currentGridRow{ int(gridRow + minosPos.y) };
			int currentGridColumn{ int(gridColumn + minosPos.x)};

			if (IsTileTaken(currentGridRow, currentGridColumn)) {
				foundPosition = true;
				break; 
			}
		}

    if (!foundPosition) {
      ++gridRow;
    }
	}

	m_Playstate.fieldPosition.x = gridColumn;
	m_Playstate.fieldPosition.y = gridRow - 1;
	PlaceTetromino();
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


	ClearLines();
	NextTetromino();
  Mix_PlayChannel(-1, m_PlaceSoundPtr, 0);
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