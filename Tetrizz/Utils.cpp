#include "pch.h"
#include "Utils.h"

int RandInt(int min, int max)
{
  int scaledMax{ (max - min) + 1 };
  return rand() % scaledMax + min;
}

float RandFloat(float min, float max, int decimals)
{
  int scale{ (int)pow(10, decimals) };
  int scaledMax{ int((max - min) * scale) };
  return rand() % (scaledMax + 1) / float(scale) + min;
}

void DrawString(const std::string& output, const Point2f topLeft, const int fontSize, const Color4f& color, const std::string& fontLocation)
{
  Texture texturePtr;
  TextureFromString(output, fontLocation, fontSize, color, texturePtr);
  DrawTexture(texturePtr, topLeft);
  DeleteTexture(texturePtr);
}

float Lerp(float start, float end, float t)
{
  t = std::max(0.0f, std::min(1.0f, t));
  return start + t * (end - start);
}

Color4f Lerp(const Color4f& start, const Color4f& end, float t)
{
  t = std::max(0.0f, std::min(1.0f, t));
  return {
      start.r + t * (end.r - start.r),
      start.g + t * (end.g - start.g),
      start.b + t * (end.b - start.b),
      start.a + t * (end.a - start.a)
  };
}

void Quit()
{
  RemoveWindow(0);
  SDL_Quit();
}
