#include "pch.h"
#include "GameScreen.h"

ScreenManager::~ScreenManager()
{
  delete m_CurrentScreen;
}

void ScreenManager::SetScreen(GameScreen* newScreen)
{
  delete m_CurrentScreen;
  m_CurrentScreen = newScreen;
}

GameScreen* ScreenManager::GetScreen()
{
  return m_CurrentScreen;
}