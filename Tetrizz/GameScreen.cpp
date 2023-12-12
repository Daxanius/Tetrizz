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

void ScreenManager::SetParent(ScreenManager* parent)
{
  delete m_Parent;
  m_Parent = parent;
}

GameScreen* ScreenManager::GetScreen()
{
  return m_CurrentScreen;
}

ScreenManager* ScreenManager::GetParent()
{
  return m_Parent == nullptr ? this : m_Parent; // Return self if parent is null
}
