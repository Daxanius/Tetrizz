#include "pch.h"
#include "MenuScreen.h"

MenuScreen::MenuScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048) < 0) {
    SDL_Quit(); // Quit SDL if Mixer initialization fails
  }

  m_MusicPtr = Mix_LoadWAV("../Resources/hard.wav");
  Mix_PlayChannel(-1, m_MusicPtr, -1);
}

MenuScreen::~MenuScreen()
{
  Mix_CloseAudio();
}

void MenuScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  DrawString("Tetrizz", { centerX - 90, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, "Resources/dhurjati.otf");
  DrawString("Click to start", { centerX - 95, 100 }, 40, { 1.f, 1.f, 1.f, 1.f }, "Resources/dhurjati.otf");
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
