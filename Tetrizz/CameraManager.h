#pragma once
#include <Core.h>
#include "Utils.h"

class CameraManager
{
public:
  void SetShake(float intensity, int duration);
  void Update();

private:
  int   m_ShakeTicks{};
  float m_ShakeIntensity{};

  void Shake() const;
};