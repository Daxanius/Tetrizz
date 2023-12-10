#include "pch.h"
#include "Playfield.h"

Playfield::Playfield(const Tetromino tetrominosArr[], int tetrminosArrSize)
{
  m_State = new TetrominoManager({ FIELD_WIDTH / 2.f, 0 }, tetrominosArr, tetrminosArrSize);
}

Playfield::~Playfield()
{
  delete m_State;
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

Point2f Playfield::GetQuickPlacePosition()
{
  int gridColumn{ int(m_State->GetTetrominoPosition().x) };
  int gridRow{ int(m_State->GetTetrominoPosition().y) };

  bool foundPosition{};
  while (gridRow < FIELD_HEIGHT && !foundPosition)
  {
    for (int i = 0; i < MINO_COUNT; ++i)
    {
      Point2f minosPos{ m_State->GetTetromino()->GetMinos()[i] };
      int currentGridRow{ int(gridRow + minosPos.y) };
      int currentGridColumn{ int(gridColumn + minosPos.x) };

      if (IsTileTaken(currentGridRow, currentGridColumn)) {
        foundPosition = true;
        break;
      }
    }

    if (!foundPosition) {
      ++gridRow;
    }
  }

  return {
    (float)gridColumn,
    (float)gridRow -1
  };
}

void Playfield::MoveLineDown(int line)
{
  for (int index{}; index < FIELD_WIDTH; index++)
  {
    m_GridArr[line + 1][index] = m_GridArr[line][index];
    m_GridArr[line][index] = nullptr;
  }
}

void Playfield::MoveLinesDown()
{
  for (int rowIndex = FIELD_HEIGHT - 1; rowIndex > 0; --rowIndex)
  {
    while (IsLineEmpty(rowIndex) && !IsLineEmpty(rowIndex - 1))
    {
      MoveLineDown(rowIndex - 1);
      ++rowIndex;
    }
  }
}

int Playfield::ClearFullLines()
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

  return linesCleared;
}

bool Playfield::Move(Point2f direction, int rotations)
{
  if (!CanMove(direction, rotations)) {
    return false;
  }

  for (int i = 0; i < rotations; ++i) {
    m_State->GetTetromino()->Rotate();
  }

  m_State->SetTetrominoPosition({
     m_State->GetTetrominoPosition().x + direction.x,
     m_State->GetTetrominoPosition().y + direction.y
  });

  return true;
}

bool Playfield::IsTileTaken(int row, int col) const
{
  return col < 0 || col >= FIELD_WIDTH || row >= FIELD_HEIGHT || row < 0 || m_GridArr[row][col] != nullptr;
}

bool Playfield::CanMove(Point2f direction, int rotations) const
{
  Tetromino t = Tetromino(*m_State->GetTetromino());

  for(int i = 0; i < rotations; ++i) {
    t.Rotate();
  }

	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ t.GetMinos()[i] };
		int gridColumn{ int(m_State->GetTetrominoPosition().x + minosPos.x + direction.x)};
		int gridRow{ int((m_State->GetTetrominoPosition().y + minosPos.y) + direction.y ) };

    if (IsTileTaken(gridRow, gridColumn)) {
      return false;
    }
	}

	return true;
}

void Playfield::QuickPlace()
{
  m_State->SetTetrominoPosition(GetQuickPlacePosition());
}

bool Playfield::PlaceTetromino()
{
  bool success = true;

	for (int i = 0; i < MINO_COUNT; ++i)
	{
		Point2f minosPos{ m_State->GetTetromino()->GetMinos()[i]};
		int gridColumn{ int(m_State->GetTetrominoPosition().x + minosPos.x)};
		int gridRow{ int(m_State->GetTetrominoPosition().y + minosPos.y) };

    if (IsTileTaken(gridRow, gridColumn)) {
      success = false;
      continue;
    }

		m_GridArr[gridRow][gridColumn] = new Color4f{ m_State->GetTetromino()->GetColor() };
	}
  return success;
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

  Tetromino* currentTetromino = m_State->GetTetromino();
  Point2f tetrominoPosition = m_State->GetTetrominoPosition();
  Point2f quickPlacePosition = GetQuickPlacePosition();

  currentTetromino->Draw({
    tetrominoPosition.x * TILE_SIZE + position.x,
    tetrominoPosition.y * TILE_SIZE + position.y,
  });

  currentTetromino->Draw({
    quickPlacePosition.x * TILE_SIZE + position.x,
    quickPlacePosition.y * TILE_SIZE + position.y,
  }, .5f);
}

void Playfield::NextTetromino()
{
  m_State->NextTetromino();
}

void  Playfield::SaveTetromino()
{
    if (m_CanSaveTetromino)
    {
        m_State->SaveTetromino();
    }
}

TetrominoManager* Playfield::GetState()
{
    return m_State;
}

void Playfield::ResetBoard()
{
    for (int colIndex = 0; colIndex < FIELD_WIDTH; ++colIndex)
    {
        for (int rowIndex = 0; rowIndex < FIELD_HEIGHT; ++rowIndex)
        {
            m_GridArr[rowIndex][colIndex] = nullptr;
        }
    }

    m_State->Reset();
}