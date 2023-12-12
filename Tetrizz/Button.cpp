#include "pch.h"
#include "Button.h"
#include "Resource.h"
#include "GameDefines.h"

Button::Button(std::string text, Rectf area, int fontSize)
  : m_WasClicked(false), m_IsPressed(false), m_IsHovering(false)
{
  m_Text = text;
  m_FontSize = fontSize;

  Texture texture;
  TextureFromString(m_Text, FONT_MAIN, fontSize, { 1.f, 1.f, 1.f, 1.f }, texture);

  float width = area.width < texture.width ? (texture.width + PADDING) : area.width;
  float height = area.height < texture.height ? (texture.height + PADDING) : area.height;

  m_Area = {
     area.left,
     area.top,
     width,
     height
  };

  DeleteTexture(texture);
}

bool Button::WasClicked()
{
  if (m_WasClicked) {
    m_WasClicked = false;
    return true;
  }

  return false;
}

bool Button::IsPressed() const
{
  return m_IsPressed;
}

bool Button::IsHovering() const
{
  return m_IsHovering;
}

void Button::Draw() const
{
  float sizeDiff{ 0 };
  if (m_IsPressed) {
    sizeDiff = SCALE_DIFF_CLICKED;
  }

  Color4f color{
    1.f,
    1.f,
    1.f,
    1.f
  };

  if (m_IsHovering) {
    color = {
      .5f,
      .5f,
      .5f,
      1.f
    };
  }

  Texture texture;
  TextureFromString(m_Text, FONT_MAIN, m_FontSize - sizeDiff / 2.f, color, texture);

  float width = m_Area.width < texture.width ? (texture.width + PADDING) : m_Area.width;
  float height = m_Area.height < texture.height ? (texture.height + PADDING) : m_Area.height;

  const float sizeDiffHalf{ sizeDiff / 2.f };
  const Rectf area = {
    m_Area.left + sizeDiffHalf,
    m_Area.top + sizeDiffHalf,
    width - sizeDiff,
    height - sizeDiff
  };

  const Point2f textPosition{
    area.left + (area.width - texture.width) / 2.f,
    area.top + (area.height - texture.height) / 2.f
  };
  
  DrawTexture(texture, textPosition);
  DeleteTexture(texture);
}

void Button::OnMouseUp(const SDL_MouseButtonEvent& e)
{
  if (m_IsPressed) {
    m_WasClicked = true;
    m_IsPressed = false;
  }
}

void Button::OnMouseDown(const SDL_MouseButtonEvent& e)
{
  if (m_IsHovering) {
    m_IsPressed = true;
  }
}

void Button::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
  m_IsHovering = !(e.x < m_Area.left || e.x > m_Area.left + m_Area.width || e.y < m_Area.top || e.y > m_Area.top + m_Area.height);
}
