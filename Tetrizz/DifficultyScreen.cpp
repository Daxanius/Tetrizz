#include "pch.h"
#include "DifficultyScreen.h"
#include "Resource.h"

DifficultyScreen::DifficultyScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX{ windowSettings.width / 2.f };
  const float centerY{ windowSettings.height / 2.f };

  m_EasyButton = new Button("Ugly",      { centerX - 50, centerY - 60, 100, 0 }, 30);
  m_PlayButton = new Button("Average",   { centerX - 50, centerY     , 100, 0 }, 30);
  m_HardButton = new Button("Beautiful", { centerX - 50, centerY + 60, 100, 0 }, 30);
  m_BackButton = new Button("Back",      { centerX - 50, windowSettings.height - 100, 100, 0 }, 30);
}

DifficultyScreen::~DifficultyScreen()
{
  delete m_EasyButton;
  delete m_PlayButton;
  delete m_HardButton;
  delete m_BackButton;
}

void DifficultyScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX{ windowSettings.width / 2.f };
  const float centerY{ windowSettings.height / 2.f };

  DrawString("Difficulty", { centerX - 110, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  m_EasyButton->Draw();
  m_PlayButton->Draw();
  m_HardButton->Draw();
  m_BackButton->Draw();
}

void DifficultyScreen::Update(float deltaTime)
{
  if (m_EasyButton->WasClicked()) {
    // use the parent because this screen will be inside of another screen for the music
    m_ScreenManager->GetParent()->SetScreen(new TetrizzScreen(m_ScreenManager->GetParent(), Difficulty::Easy));
    return;
  }

  if (m_PlayButton->WasClicked()) {
    m_ScreenManager->GetParent()->SetScreen(new TetrizzScreen(m_ScreenManager->GetParent(), Difficulty::Normal));
    return;
  }

  if (m_HardButton->WasClicked()) {
    m_ScreenManager->GetParent()->SetScreen(new TetrizzScreen(m_ScreenManager->GetParent(), Difficulty::Hard));
    return;
  }

  if (m_BackButton->WasClicked()) {
    m_ScreenManager->SetScreen(new MenuScreen(m_ScreenManager));
    return;
  }
}

void DifficultyScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    m_ScreenManager->SetScreen(new MenuScreen(m_ScreenManager));
  }
}

void DifficultyScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  m_EasyButton->OnMouseMotion(e);
  m_PlayButton->OnMouseMotion(e);
  m_HardButton->OnMouseMotion(e);
  m_BackButton->OnMouseMotion(e);
}

void DifficultyScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_EasyButton->OnMouseDown(e);
  m_PlayButton->OnMouseDown(e);
  m_HardButton->OnMouseDown(e);
  m_BackButton->OnMouseDown(e);
}

void DifficultyScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  m_EasyButton->OnMouseUp(e);
  m_PlayButton->OnMouseUp(e);
  m_HardButton->OnMouseUp(e);
  m_BackButton->OnMouseUp(e);
}
