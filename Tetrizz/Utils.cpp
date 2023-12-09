#include "pch.h"
#include "Utils.h"

int RandInt(int min, int max)
{
  int scaledMax = (max - min) + 1;
  return rand() % scaledMax + min;
}

float RandFloat(float min, float max, int decimals)
{
  int scale = pow(10, decimals);
  int scaledMax = int((max - min) * scale);
  return rand() % (scaledMax + 1) / float(scale) + min;
}