#include "pch.h"
#include "MenuScreen.h"

MenuScreen::MenuScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::Draw()
{
}

void MenuScreen::Update(float deltaTime)
{
}

void MenuScreen::FixedUpdate(float fixedDeltaTime)
{
}

void MenuScreen::OnKeyDownEvent(SDL_Keycode key)
{
}

void MenuScreen::OnKeyUpEvent(SDL_Keycode key)
{
}

void MenuScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void MenuScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_ScreenManager->SetScreen(new TetrizzScreen(m_ScreenManager));
}

void MenuScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}
