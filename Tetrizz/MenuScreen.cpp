#include "pch.h"
#include "MenuScreen.h"
#include "Resource.h"

MenuScreen::MenuScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  m_MusicPtr = Mix_LoadWAV(THEME_MENU);
  Mix_PlayChannel(-1, m_MusicPtr, -1);
}

MenuScreen::~MenuScreen()
{
  Mix_FreeChunk(m_MusicPtr);
}

void MenuScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  DrawString("Tetrizz", { centerX - 90, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Click to start", { centerX - 95, 100 }, 40, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
}

void MenuScreen::Update(float deltaTime)
{
}

void MenuScreen::FixedUpdate(float fixedDeltaTime)
{
}

void MenuScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    SDL_Quit();
  }
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
