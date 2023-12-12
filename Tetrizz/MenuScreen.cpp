#include "pch.h"
#include "MenuScreen.h"
#include "CreditsScreen.h"
#include "DifficultyScreen.h"
#include "Resource.h"
#include "GameDefines.h"

MenuScreen::MenuScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX{ windowSettings.width / 2.f };
  const float centerY{ windowSettings.height / 2.f };

  m_PlayButton    = new Button("Play",    { centerX - 50, centerY - 60, 100, 0 }, 30);
  m_CreditsButton = new Button("Credits", { centerX - 50, centerY     , 100, 0 }, 30);
  m_ExitButton    = new Button("Quit",    { centerX - 50, centerY + 60, 100, 0 }, 30);
}

MenuScreen::~MenuScreen()
{
  delete m_PlayButton;
  delete m_CreditsButton;
  delete m_ExitButton;
}

void MenuScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX{ windowSettings.width / 2.f };
  const float centerY{ windowSettings.height / 2.f };

  DrawString("Tetrizz", { centerX - 90, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Test your rizz", { centerX - 100, 100 }, 40, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  m_PlayButton->Draw();
  m_CreditsButton->Draw();
  m_ExitButton->Draw();
}

void MenuScreen::Update(float deltaTime)
{
  if (m_PlayButton->WasClicked()) {
    m_ScreenManager->SetScreen(new DifficultyScreen(m_ScreenManager));
    return;
  }

  if (m_CreditsButton->WasClicked()) {
    m_ScreenManager->SetScreen(new CreditsScreen(m_ScreenManager));
    return;
  }

  if (m_ExitButton->WasClicked()) {
    Quit();
    return;
  }
}

void MenuScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    Quit();
  }
}

void MenuScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  m_PlayButton->OnMouseMotion(e);
  m_CreditsButton->OnMouseMotion(e);
  m_ExitButton->OnMouseMotion(e);
}

void MenuScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_PlayButton->OnMouseDown(e);
  m_CreditsButton->OnMouseDown(e);
  m_ExitButton->OnMouseDown(e);
}

void MenuScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  m_PlayButton->OnMouseUp(e);
  m_CreditsButton->OnMouseUp(e);
  m_ExitButton->OnMouseUp(e);
}