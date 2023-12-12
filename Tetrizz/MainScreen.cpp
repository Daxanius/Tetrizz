#include "pch.h"
#include "MainScreen.h"
#include "MenuScreen.h"
#include "Resource.h"

MainScreen::MainScreen(ScreenManager* screenManager)
{
  m_ParentScreenManager = screenManager;
  m_ScreenManager = ScreenManager();
  m_ScreenManager.SetParent(m_ParentScreenManager);
  m_ScreenManager.SetScreen(new MenuScreen(&m_ScreenManager));

  m_MusicPtr = Mix_LoadWAV(THEME_MENU);
  Mix_PlayChannel(-1, m_MusicPtr, -1);
}

MainScreen::~MainScreen()
{
  Mix_FreeChunk(m_MusicPtr);
}

void MainScreen::Draw()
{
  m_ScreenManager.GetScreen()->Draw();
}

void MainScreen::Update(float deltaTime)
{
  m_ScreenManager.GetScreen()->Update(deltaTime);
}

void MainScreen::FixedUpdate(float fixedDeltaTime)
{
  m_ScreenManager.GetScreen()->FixedUpdate(fixedDeltaTime);
}

void MainScreen::OnKeyDownEvent(SDL_Keycode key)
{
  m_ScreenManager.GetScreen()->OnKeyDownEvent(key);
}

void MainScreen::OnKeyUpEvent(SDL_Keycode key)
{
  m_ScreenManager.GetScreen()->OnKeyUpEvent(key);
}

void MainScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  m_ScreenManager.GetScreen()->OnMouseMotionEvent(e);
}

void MainScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_ScreenManager.GetScreen()->OnMouseDownEvent(e);
}

void MainScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  m_ScreenManager.GetScreen()->OnMouseUpEvent(e);
}
