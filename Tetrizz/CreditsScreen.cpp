#include "pch.h"
#include "CreditsScreen.h"
#include "Resource.h"
#include "MenuScreen.h"

CreditsScreen::CreditsScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;

  m_BackButton = new Button("Back", { centerX - 50, windowSettings.height - 100, 100, 0 }, 30);
}

CreditsScreen::~CreditsScreen()
{
  delete m_BackButton;
}

void CreditsScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  DrawString("Credits", { centerX - 90, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  DrawString("Programming:", { centerX - 120, 100 }, 50, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Balder Huybreghs", { centerX - 120, 160 }, 35, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Quentin Demuynck", { centerX - 120, 200 }, 35, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  DrawString("Music:", { centerX - 120, 250 }, 50, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Balder Huybreghs", { centerX - 120, 310 }, 35, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Silas Ruckebusch", { centerX - 120, 350 }, 35, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  m_BackButton->Draw();
}

void CreditsScreen::Update(float deltaTime)
{
  if (m_BackButton->IsPressed()) {
    m_ScreenManager->SetScreen(new MenuScreen(m_ScreenManager));
  }
}

void CreditsScreen::FixedUpdate(float fixedDeltaTime)
{
}

void CreditsScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    m_ScreenManager->SetScreen(new MenuScreen(m_ScreenManager));
  }
}

void CreditsScreen::OnKeyUpEvent(SDL_Keycode key)
{
}

void CreditsScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  m_BackButton->OnMouseMotion(e);
}

void CreditsScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_BackButton->OnMouseDown(e);
}

void CreditsScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  m_BackButton->OnMouseUp(e);
}
