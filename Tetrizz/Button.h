#pragma once
#include <Core.h>

static const float PADDING{ 0 };
static const float SCALE_DIFF_CLICKED{ 5 };

class Button
{
public:
  Button(std::string text, Rectf area, int fontSize);

  bool        WasClicked(); // Checks if the button was pressed, will reset the pressed state when called
  bool        IsPressed(); // Checks if the button was pressed, will reset the pressed state when called
  void        Draw() const;

  void        OnMouseUp(const SDL_MouseButtonEvent& e);
  void        OnMouseDown(const SDL_MouseButtonEvent& e);
private:
  bool        m_IsPressed;
  bool        m_WasClicked;

  std::string m_Text;
  Rectf       m_Area;
  int         m_FontSize;
};