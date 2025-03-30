// [DYSON] Originally util, this file has been modified to manage more low level concepts such as SDL and Windowing
#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "structs.h"

/// [DYSON]
/// Floating point pi, changed it to be constant and convert
/// double pi to floating point pi
const float g_Pi{ float(M_PI) };

// [DYSON] These functions are used internally by the engine and should
// not be called in your game project itself
#pragma region internal
void Initialize();
void Cleanup();
#pragma endregion internal

#pragma region windowFunctionality
/// [DYSON]
/// A function that fetches some system information
/// through SDL such as display size and refresh rate.
SDL_DisplayMode GetDisplayMode();

/// [DYSON]
/// Swaps the backbuffer with the frontbuffer to redraw the
/// window with the given id
void DrawWindow(int id);

/// [DYSON]
/// Swaps the backbuffer with the frontbuffer to redraw the currently
/// selected window.
void DrawWindow();

/// [DYSON] 
/// Creates a window and returns its id.
/// Dyson allows you to create multiple windows hence it's important
/// to keep track of in some way.
/// Note that this changes the current window to the new window.
int MakeWindow(WindowSettings settings);

/// [DYSON]
/// Removes a window with the given id
void RemoveWindow(int id);

/// [DYSON]
/// Set the current drawing / working window.
/// This can be called anytime during draw to render on all windows.
/// Will crash if the window does not exist.
void SetWindow(int id);

/// [DYSON]
/// Gets the id of the window currently set
int GetCurrentWindow();

/// [DYSON]
/// Changes the window settings of the currently selected
/// window.
void SetWindowSettings(WindowSettings settings);

/// [DYSON]
/// Gets information about the window with id.
WindowSettings GetWindowInfo(int id);

/// [DYSON]
/// Gets information about the current window.
WindowSettings GetWindowInfo();

#pragma endregion windowFunctionality

/// [DYSON] An implementation for camera positioning
#pragma region CameraFunctionality
/// [DYSON] Move the camera in a direction
void MoveCamera(float x, float y);

/// [DYSON] Move the camera to a position
void MoveCamera(Point2f pos);

/// [DYSON] Rotate the camera around a set axis
void RotateCamera(float rot, float x = 0.0f, float y = 0.0f, float z = 1.0f);

/// [DYSON] Set the camera position and rotation
void SetCamera(float x, float y, float rot, float rx = 0.0f, float ry = 0.0f, float rz = 1.0f);

/// [DYSON] Set the camera position and rotation
void SetCamera(Point2f pos, float rot, float rx = 0.0f, float ry = 0.0f, float rz = 1.0f);
#pragma endregion

#pragma region OpenGLDrawFunctionality
void ClearBackground(float r, float g, float b);
void ClearBackground();
// Choose a floating point value for each color component between 0.0f and 1.0f. The a (alpha) is optional.
// Usage: SetColor(1.0f, 0.0f, 0.0f); set the drawing color to red
void SetColor(float r, float g, float b, float a = 1);
// Pass a Color4f object to the function
void SetColor(const Color4f& color);

// Draws a line by connecting the two points specified by (x1,y1) and (x2,y2)
void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
// Draws a line by connecting the two points specified by p1 and p1
void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth = 1.0f);

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth = 1);
void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth = 1);
void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3);
void DrawRect(float left, float top, float width, float height, float lineWidth = 1.0f);
void DrawRect(const Point2f& topLeft, float width, float height, float lineWidth = 1.0f);
void DrawRect(const Rectf& rect, float lineWidth = 1.0f);
void FillRect(float left, float top, float width, float height);
void FillRect(const Point2f& topLeft, float width, float height);
void FillRect(const Rectf& rect);

void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth = 1.0f);
void DrawEllipse(const Ellipsef& ellipse, float lineWidth = 1.0f);
void FillEllipse(float centerX, float centerY, float radX, float radY);
void FillEllipse(const Ellipsef& ellipse);
void FillEllipse(const Point2f& center, float radX, float radY);

// Draws an arc. The angle parameters are in radians, not in degrees.
void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
// Draws an arc. The angle parameters are in radians, not in degrees.
void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
// Fills an arc. The angle parameters are in radians, not in degrees.
void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
// Fills an arc. The angle parameters are in radians, not in degrees.
void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle);

void DrawPolygon(const std::vector<Point2f>& vertices, bool closed = true, float lineWidth = 1.0f);
void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed = true, float lineWidth = 1.0f);
void FillPolygon(const std::vector<Point2f>& vertices);
void FillPolygon(const Point2f* pVertices, size_t nrVertices);
#pragma endregion OpenGLDrawFunctionality

#pragma region TextureFunctionality

struct Texture
{
	GLuint id;
	float width;
	float height;
};

bool TextureFromFile(const std::string& path, Texture& texture);
bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& textColor, Texture& texture);
bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture);
void TextureFromSurface(const SDL_Surface* pSurface, Texture& textureData);

/// [DYSON]
/// Modified to allow texture rotations
void DrawTexture(const Texture& texture, const Point2f& dstTopLeft, const Rectf& srcRect = {}, float rotation = 0.f);

/// [DYSON]
/// Modified to allow texture rotations
void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect = {}, float rotation = 0.f);
void DeleteTexture(Texture& texture);
#pragma endregion TextureFunctionality