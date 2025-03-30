#include "pch.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Core.h"

struct Window
{
  SDL_Window* pWindow; // The window we'll be rendering to
  SDL_GLContext pContext; // OpenGL context
  WindowSettings settings;
};

// [DYSON] A custom Window system for managing multiple window instances
std::unordered_map<int, Window> g_Windows{};
int g_CurrentWindow{};
int g_IdTracker{};

#pragma region errors
void QuitOnSDLError()
{
  std::cout << "Problem during SDL initialization: ";
  std::cout << SDL_GetError();
  std::cout << std::endl;
  Cleanup();
  exit(-1);
}

void QuitOnOpenGlError()
{
  std::cout << "Problem during OpenGL initialization: ";
  std::cout << SDL_GetError();
  std::cout << std::endl;
  Cleanup();
  exit(-1);
}

void QuitOnImageError()
{
  std::cout << "Problem during SDL_image initialization: ";
  std::cout << IMG_GetError();
  std::cout << std::endl;
  Cleanup();
  exit(-1);
}

void QuitOnTtfError()
{
  std::cout << "Problem during SDL_ttf initialization: ";
  std::cout << TTF_GetError();
  std::cout << std::endl;
  Cleanup();
  exit(-1);
}

void QuitOnMessage(std::string message)
{
  std::cout << message << std::endl;
  Cleanup();
  exit(-1);
}
#pragma endregion errors

#pragma region internal
void Initialize()
{
  //Use OpenGL 2.1
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  //Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    QuitOnSDLError();
  }

  //Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    QuitOnImageError();
  }

  //Initialize SDL_ttf
  if (TTF_Init() == -1)
  {
    QuitOnTtfError();
  }
}

void Cleanup()
{
  for (auto& windowPair : g_Windows)
  {
    // Get the window and context from the pair
    Window& window{ windowPair.second };

    // Make the window's context current
    SDL_GL_MakeCurrent(window.pWindow, window.pContext);

    // Clean up the OpenGL context
    SDL_GL_DeleteContext(window.pContext);

    // Destroy the SDL window
    SDL_DestroyWindow(window.pWindow);
  }

  //Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
#pragma endregion internal

#pragma region windowFunctionality
SDL_DisplayMode GetDisplayMode()
{
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  return DM;
}

void DrawWindow(int id)
{
  auto pair{ g_Windows.find(id) };
  Window window = pair->second;
  SDL_GL_SwapWindow(window.pWindow);
}

void DrawWindow()
{
  DrawWindow(g_CurrentWindow);
}

int MakeWindow(WindowSettings settings)
{
  //Create window
  SDL_Window* pWindow{ SDL_CreateWindow(
    settings.title.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      int(settings.width),
      int(settings.height),
      SDL_WINDOW_OPENGL
   ) };

  if (pWindow == nullptr)
  {
    QuitOnSDLError();
  }

  // Create an opengl context and attach it to the window 
  SDL_GLContext pContext{ SDL_GL_CreateContext(pWindow) };
  if (pContext == nullptr)
  {
    QuitOnSDLError();
  }

  // [DYSON] Set all the window settings
  SDL_SetWindowFullscreen(pWindow, settings.fullscreenFlags);
  SDL_SetWindowAlwaysOnTop(pWindow, (SDL_bool)settings.alwaysOnTop);
  SDL_SetWindowBordered(pWindow, (SDL_bool)settings.bordered);
  SDL_SetWindowPosition(pWindow, settings.posX, settings.posY);
  SDL_SetWindowOpacity(pWindow, settings.opacity);

  if (settings.vsync)
  {
    // Synchronize buffer swap with the monitor's vertical refresh
    if (SDL_GL_SetSwapInterval(1) < 0)
    {
      QuitOnSDLError();
    }
  } else
  {
    SDL_GL_SetSwapInterval(0);
  }

  // Initialize Projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the clipping (viewing) area's left, right, top and top
  gluOrtho2D(0, settings.width, settings.height, 0);// y from top to top

  // The viewport is the rectangular region of the window where the image is drawn.
  // Set it to the entire client area of the created window
  glViewport(0, 0, int(settings.width), int(settings.height));

  //Initialize Modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // [DYSON] Enable line smoothing for cleaner geometry
  if (settings.lineSmoothing) {
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_MULTISAMPLE);
  }

  // Enable color blending and use alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Window engineWindow{
    pWindow,
    pContext,
    settings
  };

  g_CurrentWindow = g_IdTracker;
  g_Windows.insert({ g_IdTracker, engineWindow });
  return g_IdTracker++;
}

void RemoveWindow(int id)
{
  auto pair{ g_Windows.find(id) };
  if (id == g_CurrentWindow || pair == g_Windows.end()) {
    QuitOnMessage("The given window does not exist or the window is currently selected");
  }

  Window window{ pair->second };
  SDL_GL_DeleteContext(window.pContext);
  SDL_DestroyWindow(window.pWindow);
  g_Windows.erase(id);
}

void SetWindow(int id)
{
  auto pair{ g_Windows.find(id) };
  if (pair == g_Windows.end()) {
    QuitOnMessage("Window not found");
  }

  Window window{ pair->second };
  SDL_GL_MakeCurrent(window.pWindow, window.pContext);
  g_CurrentWindow = id;
}

int GetCurrentWindow()
{
  return g_CurrentWindow;
}

void SetWindowSettings(WindowSettings settings)
{
  auto pair{ g_Windows.find(g_CurrentWindow) };

  // Update the existing window's settings
  Window& window = pair->second;
  window.settings = settings;

  // Apply the updated settings
  SDL_SetWindowTitle(window.pWindow, settings.title.c_str());
  SDL_SetWindowFullscreen(window.pWindow, settings.fullscreenFlags);
  SDL_SetWindowSize(window.pWindow, (int)settings.width, (int)settings.height);
  SDL_SetWindowAlwaysOnTop(window.pWindow, (SDL_bool)settings.alwaysOnTop);
  SDL_SetWindowBordered(window.pWindow, (SDL_bool)settings.bordered);
  SDL_SetWindowPosition(window.pWindow, settings.posX, settings.posY);
  SDL_SetWindowOpacity(window.pWindow, settings.opacity);

  // Update the projection matrix based on the new settings
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, settings.width, settings.height, 0);
  glViewport(0, 0, int(settings.width), int(settings.height));

  if (settings.lineSmoothing) {
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_MULTISAMPLE);
  } else {
    glDisable(GL_LINE_SMOOTH);
    glHint(GL_POLYGON_SMOOTH, GL_FASTEST);
    glDisable(GL_MULTISAMPLE);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

WindowSettings GetWindowInfo(int id)
{
  auto pair{ g_Windows.find(id) };

  int width, height;
  SDL_GetWindowSize(pair->second.pWindow, &width, &height);

  // Update the window size in the stored settings
  pair->second.settings.width = static_cast<float>(width);
  pair->second.settings.height = static_cast<float>(height);

  return pair->second.settings;
}

WindowSettings GetWindowInfo()
{
  return GetWindowInfo(g_CurrentWindow);
}

#pragma endregion windowFunctionality

#pragma region CameraFunctionality
void MoveCamera(float x, float y)
{
  glTranslatef(x, y, 0);
}

void MoveCamera(Point2f pos)
{
  MoveCamera(pos.x, pos.y);
}

void RotateCamera(float rot, float x, float y, float z)
{
  WindowSettings settings{ GetWindowInfo() };
  glTranslatef(settings.width / 2.0f, settings.height / 2.0f, 0.0f);
  glRotatef(rot, x, y, z);
  glTranslatef(-settings.width / 2.0f, -settings.height / 2.0f, 0.0f);
}

void SetCamera(float x, float y, float rot, float rx, float ry, float rz)
{
  glLoadIdentity();  // Reset the modelview matrix
  MoveCamera(x, y);
  RotateCamera(rot, rx, ry, rz);
}

void SetCamera(Point2f pos, float rot, float rx, float ry, float rz)
{
  SetCamera(pos.x, pos.y, rot, rx, ry, rz);
}
#pragma endregion CameraFunctionality

#pragma region OpenGLDrawFunctionality
void ClearBackground(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ClearBackground()
{
	ClearBackground(185.0f / 255.0f, 211.0f / 255.0f, 238.0f / 255.0f);
}

void SetColor(float r, float g, float b, float a)
{
	glColor4f(r, g, b, a);
}

void SetColor(const Color4f& color)
{
	glColor4f(color.r, color.g, color.b, color.a);
}

void DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

void DrawLine(const Point2f& p1, const Point2f& p2, float lineWidth)
{
	DrawLine(p1.x, p1.y, p2.x, p2.y, lineWidth);
}

void DrawRect(float left, float top, float width, float height, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(left, top);
		glVertex2f(left + width, top);
		glVertex2f(left + width, top + height);
		glVertex2f(left, top + height);
	}
	glEnd();
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
	}
	glEnd();
}

void DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth)
{
	DrawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, lineWidth);
}

void FillTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
	}
	glEnd();
}

void FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3)
{
	FillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void DrawRect(const Point2f& topLeft, float width, float height, float lineWidth)
{
	DrawRect(topLeft.x, topLeft.y, width, height, lineWidth);
}

void DrawRect(const Rectf& rect, float lineWidth)
{
	DrawRect(rect.left, rect.top, rect.width, rect.height, lineWidth);
}

void FillRect(float left, float top, float width, float height)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(left, top);
		glVertex2f(left + width, top);
		glVertex2f(left + width, top + height);
		glVertex2f(left, top + height);
	}
	glEnd();
}

void FillRect(const Point2f& topLeft, float width, float height)
{
	FillRect(topLeft.x, topLeft.y, width, height);
}

void FillRect(const Rectf& rect)
{
	FillRect(rect.left, rect.top, rect.width, rect.height);
}

void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
{
	float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
	}
	glEnd();
}

void DrawEllipse(const Point2f& center, float radX, float radY, float lineWidth)
{
	DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void DrawEllipse(const Ellipsef& ellipse, float lineWidth)
{
	DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth);
}

void FillEllipse(float centerX, float centerY, float radX, float radY)
{
	float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

	glBegin(GL_POLYGON);
	{
		for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
	}
	glEnd();
}

void FillEllipse(const Ellipsef& ellipse)
{
	FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
}

void FillEllipse(const Point2f& center, float radX, float radY)
{
	FillEllipse(center.x, center.y, radX, radY);
}

void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	if (fromAngle > tillAngle)
	{
		return;
	}

	//flip the angles (because view is flipped)
	fromAngle *= -1;
	tillAngle *= -1;
	std::swap(fromAngle, tillAngle); //from becomes to and vice versa

	float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	{
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
	}
	glEnd();

}

void DrawArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
}

void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
{
	if (fromAngle > tillAngle)
	{
		return;
	}

	//flip the angles (because view is flipped)
	fromAngle *= -1;
	tillAngle *= -1;
	std::swap(fromAngle, tillAngle); //from becomes to and vice versa

	float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

	glBegin(GL_POLYGON);
	{
		glVertex2f(centerX, centerY);
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * float(cos(angle)), centerY + radY * float(sin(angle)));
		}
		glVertex2f(centerX + radX * float(cos(tillAngle)), centerY + radY * float(sin(tillAngle)));
	}
	glEnd();
}

void FillArc(const Point2f& center, float radX, float radY, float fromAngle, float tillAngle)
{
	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
}

void DrawPolygon(const std::vector<Point2f>& vertices, bool closed, float lineWidth)
{
	DrawPolygon(vertices.data(), vertices.size(), closed, lineWidth);
}

void DrawPolygon(const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth)
{
	glLineWidth(lineWidth);
	closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
	{
		for (size_t idx{ 0 }; idx < nrVertices; ++idx)
		{
			glVertex2f(pVertices[idx].x, pVertices[idx].y);
		}
	}
	glEnd();
}

void FillPolygon(const std::vector<Point2f>& vertices)
{
	FillPolygon(vertices.data(), vertices.size());
}

void FillPolygon(const Point2f* pVertices, size_t nrVertices)
{
	glBegin(GL_POLYGON);
	{
		for (size_t idx{ 0 }; idx < nrVertices; ++idx)
		{
			glVertex2f(pVertices[idx].x, pVertices[idx].y);
		}
	}
	glEnd();
}
#pragma endregion OpenGLDrawFunctionality

#pragma region textureImplementations

bool TextureFromFile(const std::string& path, Texture& texture)
{
	//Load file for use as an image in a new surface.
	SDL_Surface* pLoadedSurface = IMG_Load((path).c_str());
	if (pLoadedSurface == nullptr)
	{
		std::cerr << "TextureFromFile: SDL Error when calling IMG_Load: " << SDL_GetError() << std::endl;
		return false;
	}

	TextureFromSurface(pLoadedSurface, texture);

	//Free loaded surface
	SDL_FreeSurface(pLoadedSurface);

	return true;
}

bool TextureFromString(const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor, Texture& texture)
{
	// Create font
	TTF_Font* pFont{};
	pFont = TTF_OpenFont((fontPath).c_str(), ptSize);
	if (pFont == nullptr)
	{
		std::cout << "TextureFromString: Failed to load font! SDL_ttf Error: " << TTF_GetError();
		std::cin.get();
		return false;
	}

	// Create texture using this fontand close font afterwards
	bool textureOk = TextureFromString(text, pFont, textColor, texture);
	TTF_CloseFont(pFont);

	return textureOk;
}

bool TextureFromString(const std::string& text, TTF_Font* pFont, const Color4f& color, Texture& texture)
{
	if (pFont == nullptr)
	{
		std::cerr << "Texture::CreateFromString, invalid TTF_Font pointer\n";
		return false;
	}

	//Render text surface
	SDL_Color textColor{};
	textColor.r = Uint8(color.r * 255);
	textColor.g = Uint8(color.g * 255);
	textColor.b = Uint8(color.b * 255);
	textColor.a = Uint8(color.a * 255);

	SDL_Surface* pLoadedSurface = TTF_RenderText_Blended(pFont, text.c_str(), textColor);
	//SDL_Surface* pLoadedSurface = TTF_RenderText_Solid(pFont, textureText.c_str(), textColor);
	if (pLoadedSurface == nullptr)
	{
		std::cerr << "TextureFromString: Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
		return false;
	}

	// copy to video memory
	TextureFromSurface(pLoadedSurface, texture);

	//Free loaded surface
	SDL_FreeSurface(pLoadedSurface);

	return true;
}

void TextureFromSurface(const SDL_Surface* pSurface, Texture& texture)
{
	//Get image dimensions
	texture.width = float(pSurface->w);
	texture.height = float(pSurface->h);

	// Get pixel format information and translate to OpenGl format
	GLenum pixelFormat{ GL_RGB };
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGB;
		}
		else
		{
			pixelFormat = GL_BGR;
		}
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
		{
			pixelFormat = GL_RGBA;
		}
		else
		{
			pixelFormat = GL_BGRA;
		}
		break;
	default:
		std::cerr << "TextureFromSurface error: Unknow pixel format, BytesPerPixel: " << pSurface->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";;
		texture.width = 0;
		texture.height = 0;
		return;
	}

	//Generate an array of textures.  We only want one texture (one element array), so trick
	//it by treating "texture" as array of length one.
	glGenTextures(1, &texture.id);

	//Select (bind) the texture we just generated as the current 2D texture OpenGL is using/modifying.
	//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, pSurface->pitch / pSurface->format->BytesPerPixel);

	// check for errors.
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		std::cerr << "TextureFromSurface, error binding textures, Error id = " << e << '\n';
		std::cerr << "Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).\n";
		std::cerr << "There might be a white rectangle instead of the image.\n";
		texture.width = 0;
		texture.height = 0;
		return;
	}

	//Specify the texture's data.  This function is a bit tricky, and it's hard to find helpful documentation.  A summary:
	//   GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
	//               0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
	//                         not cached smaller copies)
	//         GL_RGBA:    Specifies the number of color components in the texture.
	//                     This is how OpenGL will store the texture internally (kinda)--
	//                     It's essentially the texture's type.
	//      surface->w:    The width of the texture
	//      surface->h:    The height of the texture
	//               0:    The border.  Don't worry about this if you're just starting.
	//     pixelFormat:    The format that the *data* is in--NOT the texture! 
	//GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
	//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
	//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
	//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
	// surface->pixels:    The actual data.  As above, SDL's array of bytes.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	//Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
	//*smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
	//each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
	//further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
	//them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void DeleteTexture(Texture& texture)
{
	glDeleteTextures(1, &texture.id);
}

void DrawTexture(const Texture& texture, const Point2f& dstTopLeft, const Rectf& srcRect, float rotation)
{
	Rectf dstRect{ dstTopLeft.x, dstTopLeft.y, srcRect.width, srcRect.height };
	DrawTexture(texture, dstRect, srcRect, rotation);
}

void DrawTexture(const Texture& texture, const Rectf& dstRect, const Rectf& srcRect, float rotation)
{
	// Determine texture coordinates using srcRect and default destination width and height
	float textLeft{};
	float textRight{};
	float textTop{};
	float textBottom{};

	float defaultDstWidth{};
	float defaultDstHeight{};
	if (!(srcRect.width > 0.0f && srcRect.height > 0.0f)) // No srcRect specified
	{
		// Use complete texture
		textLeft = 0.0f;
		textRight = 1.0f;
		textTop = 0.0f;				
		textBottom = 1.0f;			

		defaultDstHeight = texture.height;
		defaultDstWidth = texture.width;
	}
	else // srcRect specified
	{
		textLeft = srcRect.left / texture.width;
		textRight = (srcRect.left + srcRect.width) / texture.width;
		textTop = srcRect.top / texture.height;
		textBottom = (srcRect.top + srcRect.height) / texture.height;

		defaultDstHeight = srcRect.height;
		defaultDstWidth = srcRect.width;
	}

	// Determine vertex coordinates
	float vertexTop{ dstRect.top };
	float vertexLeft{ dstRect.left };
	float vertexBottom{};
	float vertexRight{};
	if (!(dstRect.width > 0.001f && dstRect.height > 0.001f)) // If no size specified use default size
	{
		vertexRight = vertexLeft + defaultDstWidth;
		vertexBottom = vertexTop + defaultDstHeight;
	}
	else
	{
		vertexRight = vertexLeft + dstRect.width;
		vertexBottom = vertexTop + dstRect.height;
	}

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // [DYSON] Translate to the center of the destination rectangle
  glTranslatef(dstRect.left + dstRect.width / 2.0f, dstRect.top + dstRect.height / 2.0f, 0.0f);

  // [DYSON] Rotate around the center
  glRotatef(rotation, 0.0f, 0.0f, 1.0f);

  // [DYSON] Translate back to the original position
  glTranslatef(-(dstRect.left + dstRect.width / 2.0f), -(dstRect.top + dstRect.height / 2.0f), 0.0f);

	// Tell opengl which texture we will use
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Draw
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS);
		{
			glTexCoord2f(textLeft, textBottom);
			glVertex2f(vertexLeft, vertexBottom);

			glTexCoord2f(textLeft, textTop);
			glVertex2f(vertexLeft, vertexTop);

			glTexCoord2f(textRight, textTop);
			glVertex2f(vertexRight, vertexTop);

			glTexCoord2f(textRight, textBottom);
			glVertex2f(vertexRight, vertexBottom);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

  glPopMatrix(); // [DYSON] Restore the previous modelview matrix
}
#pragma endregion textureImplementations