#include "pch.h"
#include "CameraManager.h"

void CameraManager::SetShake(float intensity, int ticks)
{
  m_ShakeTicks = ticks;
  m_ShakeIntensity = intensity;
}

void CameraManager::Update()
{
  if (m_ShakeTicks > 0) {
    Shake();
    --m_ShakeTicks;
    return;
  }

  SetCamera(0.f, 0.f, 0.f);
}

void CameraManager::Shake() const
{
  const float offsetX{ RandFloat(0, 1, 4) * m_ShakeIntensity };
  const float offsetY{ RandFloat(0, 1, 4) * m_ShakeIntensity };
  const float offsetRotation{ RandFloat(0, 1, 4) * m_ShakeIntensity };

  SetCamera(offsetX, offsetY, offsetRotation);
}
