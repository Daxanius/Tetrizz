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
}

Playstate Playfield::GetPlaystate() const
{
  return m_Playstate;
}

bool Playfield::IsLineFull(int line) const
{
	for (int index{}; index < FIELD_WIDTH; index++)
	{
		if (m_GridArr[line][index] == nullptr)
		{
			return false;
		}
	}

	return true;
}

bool Playfield::IsLineEmpty(int line) const
{
  for (int index{}; index < FIELD_WIDTH; index++)
  {
    if (m_GridArr[line][index] != nullptr)
    {
      return false;
    }
  }

  return true;
}

void Playfield::MoveLineDown(int line)
{
  for (int index{}; index < FIELD_WIDTH; index++)
  {
    m_GridArr[line + 1][index] = m_GridArr[line][index];
    m_GridArr[line][index] = nullptr;
  }
}

void Playfield::ClearLines()
{
  int linesCleared{};

  // Clears the lines
	for (int rowIndex = 0; rowIndex < FIELD_HEIGHT; ++rowIndex)
	{
		if (IsLineFull(rowIndex))
		{
			for (int colIndex{}; colIndex < FIELD_WIDTH; colIndex++)
			{
        delete m_GridArr[rowIndex][colIndex];
				m_GridArr[rowIndex][colIndex] = nullptr;
			}

      ++linesCleared;
		}
	}

  if (linesCleared < 1) {
    return;
  }

  for (int rowIndex = FIELD_HEIGHT -1; rowIndex > 0; --rowIndex)
  {
    while (IsLineEmpty(rowIndex) && !IsLineEmpty(rowIndex - 1))
    {
      MoveLineDown(rowIndex -1);
      ++rowIndex;
    }
  }

  m_Score += linesCleared;
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
  if (CanMove({ -1, 0 }))
	{
		m_Playstate.fieldPosition.x -= 1;
	}
}

void Playfield::MoveRight()
{
	if (CanMove({ 1, 0 }))
	{
		m_Playstate.fieldPosition.x += 1;
	}
}

void Playfield::MoveDown()
{
  if (CanMove({ 0, 1 }))
	{
		m_Playstate.fieldPosition.y += 1;
	}
}

bool Playfield::CanMove(Point2f direction, bool rotates)
{
  Tetromino* t = new Tetromino(*m_Playstate.currentTetrominoPtr);

  if (rotates) {
    t->Rotate();
  }

	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ t->GetMinos()[i] };
		int gridColumn{ int(m_Playstate.fieldPosition.x + minosPos.x + direction.x ) };
		int gridRow{ int((m_Playstate.fieldPosition.y + minosPos.y) + direction.y ) };

    if (IsTileTaken(gridRow, gridColumn)) {
      return false;
    }
	}

	return true;
}

void  Playfield::Rotate()
{
  if (CanMove({ 0, 0 }, true))
	{
		m_Playstate.currentTetrominoPtr->Rotate();
    Mix_PlayChannel(-1, m_RotateSoundPtr, 0);
	}
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

	m_Playstate.fieldPosition.x = (float)gridColumn;
	m_Playstate.fieldPosition.y = (float)gridRow - 1;
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

  m_Playstate.currentTetrominoPtr->Draw({
    m_Playstate.fieldPosition.x * TILE_SIZE + position.x,
    m_Playstate.fieldPosition.y * TILE_SIZE + position.y,
  });
}

void Playfield::Update()
{
  if (!CanMove({ 0, 1 }))
	{
    PlaceTetromino();
	}	
  MoveDown();
}