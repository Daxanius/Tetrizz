#include "pch.h"
#include "MenuScreen.h"
#include "Resource.h"

MenuScreen::MenuScreen(ScreenManager* screenManager)
{
  m_ScreenManager = screenManager;

  m_MusicPtr = Mix_LoadWAV(THEME_MENU);
  Mix_PlayChannel(-1, m_MusicPtr, -1);

  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  m_NormalButton  = new Button("Normal",  { centerX - 50, centerY - 90, 100, 0 }, 30);
  m_HardButton    = new Button("Hard",    { centerX - 50, centerY - 30, 100, 0 }, 30);
  m_CreditsButton = new Button("Credits", { centerX - 50, centerY + 30, 100, 0 }, 30);
  m_ExitButton    = new Button("Quit",    { centerX - 50, centerY + 90, 100, 0 }, 30);
}

MenuScreen::~MenuScreen()
{
  delete m_NormalButton;
  delete m_HardButton;
  delete m_ExitButton;
  Mix_FreeChunk(m_MusicPtr);
}

void MenuScreen::Draw()
{
  const WindowSettings windowSettings{ GetWindowInfo() };
  const float centerX = windowSettings.width / 2.f;
  const float centerY = windowSettings.height / 2.f;

  DrawString("Tetrizz", { centerX - 90, 40 }, 70, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);
  DrawString("Test your rizz", { centerX - 100, 100 }, 40, { 1.f, 1.f, 1.f, 1.f }, FONT_MAIN);

  m_NormalButton->Draw();
  m_HardButton->Draw();
  m_CreditsButton->Draw();
  m_ExitButton->Draw();
}

void MenuScreen::Update(float deltaTime)
{
  if (m_NormalButton->WasClicked()) {
    m_ScreenManager->SetScreen(new TetrizzScreen(m_ScreenManager));
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

void MenuScreen::FixedUpdate(float fixedDeltaTime)
{
}

void MenuScreen::OnKeyDownEvent(SDL_Keycode key)
{
  if (key == SDLK_ESCAPE) {
    Quit();
  }
}

void MenuScreen::OnKeyUpEvent(SDL_Keycode key)
{

}

void MenuScreen::OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
  m_NormalButton->OnMouseMotion(e);
  m_HardButton->OnMouseMotion(e);
  m_CreditsButton->OnMouseMotion(e);
  m_ExitButton->OnMouseMotion(e);
}

void MenuScreen::OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
  m_NormalButton->OnMouseDown(e);
  m_HardButton->OnMouseDown(e);
  m_CreditsButton->OnMouseDown(e);
  m_ExitButton->OnMouseDown(e);
}

void MenuScreen::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
  m_NormalButton->OnMouseUp(e);
  m_HardButton->OnMouseUp(e);
  m_CreditsButton->OnMouseUp(e);
  m_ExitButton->OnMouseUp(e);
}