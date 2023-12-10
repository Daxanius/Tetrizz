#pragma once
#include <Core.h>
#include <queue>
#include "Utils.h"

struct AnimationGoal
{
  Point2f position;
  Color4f color;
  int size;
  int time;
  int delay;
};

class AnimatedText
{
public:
  AnimatedText(Point2f position, std::string text, int fontSize, Color4f color, std::string fontFile);

  void        AddGoal(AnimationGoal goal);
  void        Update(float deltatime);
  void        Draw();

  int         GetGoalsLeft();
  std::string GetText();
private:
  std::queue<AnimationGoal> m_Goals;
  float                     m_CurrentTime{};

  Color4f     m_Color;
  Point2f     m_Position;
  int         m_Fontsize;
  std::string m_Text;
  std::string m_FontFile;
};

