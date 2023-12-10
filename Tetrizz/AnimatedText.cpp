#include "pch.h"
#include "AnimatedText.h"

AnimatedText::AnimatedText(Point2f position, std::string text, int fontSize, Color4f color, std::string fontFile)
{
  m_Position = position;
  m_Text = text;
  m_Color = color;
  m_Fontsize = fontSize;
  m_FontFile = fontFile;
}

void AnimatedText::AddGoal(AnimationGoal goal)
{
  m_Goals.push(goal);
}

void AnimatedText::Update(float deltaTime)
{
  if (m_Goals.empty())
  {
    return;
  }

  if (m_Goals.front().delay > 0)
  {
    m_Goals.front().delay -= int(deltaTime * 1000);
    return;
  }

  float t = m_CurrentTime / float(m_Goals.front().time);
  float interpolationFactor = 0.5f - 0.5f * cosf(t * M_PI);

  m_Color = Lerp(m_Color, m_Goals.front().color, interpolationFactor);

  m_Position.x = Lerp(m_Position.x, m_Goals.front().position.x, interpolationFactor);
  m_Position.y = Lerp(m_Position.y, m_Goals.front().position.y, interpolationFactor);

  m_Fontsize = int(Lerp(float(m_Fontsize), float(m_Goals.front().size), interpolationFactor));

  m_CurrentTime += deltaTime;

  if (m_CurrentTime >= m_Goals.front().time)
  {
    m_Goals.pop();
    m_CurrentTime = 0.0f;
  }
}

void AnimatedText::Draw()
{
  DrawString(m_Text, m_Position, m_Fontsize, m_Color, m_FontFile);
}

int AnimatedText::GetGoalsLeft()
{
  return m_Goals.size();
}

std::string AnimatedText::GetText()
{
  return m_Text;
}
