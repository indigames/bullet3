
#ifdef B3_USE_SDL
#include "SDLOpenGLWindow.h"

#include <glad/gl.h>
#include <glad/egl.h>
#include <SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include "LinearMath/btScalar.h"
#include "Bullet3Common/b3Scalar.h"

struct SDLOpenGLWindowInternalData
{
	bool m_requestedExit;
	bool m_hasCursorPos;
	bool m_altPressed;
	bool m_shiftPressed;
	bool m_ctrlPressed;
	float m_cursorXPos;
	float m_cursorYPos;
	b3MouseMoveCallback m_mouseMoveCallback;
	b3MouseButtonCallback m_mouseButtonCallback;
	b3ResizeCallback m_resizeCallback;
	b3WheelCallback m_wheelCallback;
	b3KeyboardCallback m_keyboardCallback;
	b3RenderCallback m_renderCallback;
	int m_width;
	int m_height;
	float m_retinaScaleFactor;

	SDL_Window* m_sdlWindow;
	SDL_GLContext m_sdlContext;

	SDLOpenGLWindowInternalData()
		: m_requestedExit(false),
		  m_hasCursorPos(false),
		  m_altPressed(false),
		  m_shiftPressed(false),
		  m_ctrlPressed(false),
		  m_cursorXPos(0),
		  m_cursorYPos(0),
		  m_mouseMoveCallback(0),
		  m_mouseButtonCallback(0),
		  m_resizeCallback(0),
		  m_wheelCallback(0),
		  m_keyboardCallback(0),
		  m_renderCallback(0),
		  m_width(0),
		  m_height(0),
		  m_retinaScaleFactor(1),
		  m_sdlWindow(0)
	{
	}
};

static void SDLErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void SDLMouseButtonCallback(SDL_Window* window, int button, int sdlState, int)
{
	SDLOpenGLWindow* wnd = (SDLOpenGLWindow*)SDL_GetWindowData(window , "SDLOpenGLWindow");
	if (wnd && wnd->getMouseButtonCallback())
	{
		int state = (sdlState == SDL_MOUSEBUTTONDOWN) ? 1 : 0;
		wnd->mouseButtonCallbackInternal(button, state);
	}
}

static void SDLScrollCallback(SDL_Window* window, double deltaX, double deltaY)
{
	SDLOpenGLWindow* wnd = (SDLOpenGLWindow*)SDL_GetWindowData(window, "SDLOpenGLWindow");
	if (wnd && wnd->getWheelCallback())
	{
		wnd->getWheelCallback()(deltaX * 100, deltaY * 100);
	}
}

static void SDLCursorPosCallback(SDL_Window* window, double xPos, double yPos)
{
	SDLOpenGLWindow* wnd = (SDLOpenGLWindow*)SDL_GetWindowData(window, "SDLOpenGLWindow");
	if (wnd && wnd->getMouseMoveCallback())
	{
		wnd->mouseCursorCallbackInternal(xPos, yPos);
	}
}

static void SDLKeyCallback(SDL_Window* window, int key, int scancode, int action, int mods)
{
	SDLOpenGLWindow* wnd = (SDLOpenGLWindow*)SDL_GetWindowData(window, "SDLOpenGLWindow");
	if (wnd)
	{
		wnd->keyboardCallbackInternal(key, action);
	}
	if (key == SDLK_ESCAPE && action == SDL_KEYDOWN)
	{
		SDL_HideWindow(window);
		SDL_Quit();
	}
}

static void SDLSizeCallback(SDL_Window* window, int width, int height)
{
	SDLOpenGLWindow* wnd = (SDLOpenGLWindow*)SDL_GetWindowData(window, "SDLOpenGLWindow");
	{
		wnd->resizeInternal(width, height);
	}
}

SDLOpenGLWindow::SDLOpenGLWindow()
{
	m_data = new SDLOpenGLWindowInternalData();
}

SDLOpenGLWindow::~SDLOpenGLWindow()
{
	if (m_data->m_sdlWindow)
	{
		closeWindow();
	}
	delete m_data;
}

int getBulletKeyFromSDLKeycode(int sdlKeyCode)
{
	int keycode = -1;
	if (sdlKeyCode >= 'A' && sdlKeyCode <= 'Z')
	{
		return sdlKeyCode + 32;  //todo: fix the ascii A vs a input
	}
	if (sdlKeyCode >= '0' && sdlKeyCode <= '9')
	{
		return sdlKeyCode;
	}

	switch (sdlKeyCode)
	{
		case SDLK_RETURN:
		{
			keycode = B3G_RETURN;
			break;
		};
		case SDLK_ESCAPE:
		{
			keycode = B3G_ESCAPE;
			break;
		};
		case SDLK_F1:
		{
			keycode = B3G_F1;
			break;
		}
		case SDLK_F2:
		{
			keycode = B3G_F2;
			break;
		}
		case SDLK_F3:
		{
			keycode = B3G_F3;
			break;
		}
		case SDLK_F4:
		{
			keycode = B3G_F4;
			break;
		}
		case SDLK_F5:
		{
			keycode = B3G_F5;
			break;
		}
		case SDLK_F6:
		{
			keycode = B3G_F6;
			break;
		}
		case SDLK_F7:
		{
			keycode = B3G_F7;
			break;
		}
		case SDLK_F8:
		{
			keycode = B3G_F8;
			break;
		}
		case SDLK_F9:
		{
			keycode = B3G_F9;
			break;
		}
		case SDLK_F10:
		{
			keycode = B3G_F10;
			break;
		}

			//case SDLK_SPACE: {keycode= ' '; break;}

		case SDLK_PAGEDOWN:
		{
			keycode = B3G_PAGE_DOWN;
			break;
		}
		case SDLK_PAGEUP:
		{
			keycode = B3G_PAGE_UP;
			break;
		}

		case SDLK_INSERT:
		{
			keycode = B3G_INSERT;
			break;
		}
		case SDLK_BACKSPACE:
		{
			keycode = B3G_BACKSPACE;
			break;
		}
		case SDLK_DELETE:
		{
			keycode = B3G_DELETE;
			break;
		}

		case SDLK_END:
		{
			keycode = B3G_END;
			break;
		}
		case SDLK_HOME:
		{
			keycode = B3G_HOME;
			break;
		}
		case SDLK_LEFT:
		{
			keycode = B3G_LEFT_ARROW;
			break;
		}
		case SDLK_UP:
		{
			keycode = B3G_UP_ARROW;
			break;
		}
		case SDLK_RIGHT:
		{
			keycode = B3G_RIGHT_ARROW;
			break;
		}
		case SDLK_DOWN:
		{
			keycode = B3G_DOWN_ARROW;
			break;
		}
		case SDLK_RSHIFT:
		{
			keycode = B3G_SHIFT;
			break;
		}
		case SDLK_LSHIFT:
		{
			keycode = B3G_SHIFT;
			break;
		}
		case SDLK_MENU:
		{
			keycode = B3G_ALT;
			break;
		}
		case SDLK_RCTRL:
		{
			keycode = B3G_CONTROL;
			break;
		}
		case SDLK_LCTRL:
		{
			keycode = B3G_CONTROL;
			break;
		}
		default:
		{
			//keycode = MapVirtualKey( virtualKeyCode, MAPSDLK_SDLK_TO_CHAR ) & 0x0000FFFF;
		}
	};

	return keycode;
}

void SDLOpenGLWindow::keyboardCallbackInternal(int key, int state)
{
	if (getKeyboardCallback())
	{
		//convert keyboard codes from sdl to bullet
		int btcode = getBulletKeyFromSDLKeycode(key);
		int btstate = (state == SDL_KEYUP) ? 0 : 1;

		switch (btcode)
		{
			case B3G_SHIFT:
			{
				m_data->m_shiftPressed = state != 0;
				break;
			}
			case B3G_ALT:
			{
				m_data->m_altPressed = state != 0;
				break;
			}
			case B3G_CONTROL:
			{
				m_data->m_ctrlPressed = state != 0;
				break;
			}
			default:
			{
			}
		}

		getKeyboardCallback()(btcode, btstate);
	}
}

void SDLOpenGLWindow::mouseButtonCallbackInternal(int button, int state)
{
	if (getMouseButtonCallback() && m_data->m_hasCursorPos)
	{
		getMouseButtonCallback()(button, state, m_data->m_cursorXPos, m_data->m_cursorYPos);
	}
}

void SDLOpenGLWindow::mouseCursorCallbackInternal(double xPos, double yPos)
{
	if (getMouseMoveCallback())
	{
		m_data->m_hasCursorPos = true;
		m_data->m_cursorXPos = xPos;
		m_data->m_cursorYPos = yPos;
		getMouseMoveCallback()(xPos, yPos);
	}
}

void SDLOpenGLWindow::resizeInternal(int width, int height)
{
	SDL_GL_GetDrawableSize((SDL_Window*)m_data->m_sdlWindow, &m_data->m_width, &m_data->m_height);
	glViewport(0, 0, m_data->m_width, m_data->m_height);

	if (getResizeCallback())
	{
		getResizeCallback()(m_data->m_width / m_data->m_retinaScaleFactor, m_data->m_height / m_data->m_retinaScaleFactor);
	}
}

void SDLOpenGLWindow::createDefaultWindow(int width, int height, const char* title)
{
	b3gWindowConstructionInfo ci;
	ci.m_width = width;
	ci.m_height = height;
	ci.m_title = title;

	createWindow(ci);
}

extern void* getAppWindow();
extern void* getAppContext();

void SDLOpenGLWindow::createWindow(const b3gWindowConstructionInfo& ci)
{
	btAssert(m_data->m_sdlWindow == 0);
	if (m_data->m_sdlWindow == 0)
	{
		SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

#if defined(GLAD_GLES2)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
#if defined(__ANDROID__) || defined(IOS)
		flags |= SDL_WINDOW_FULLSCREEN;
#else
		flags |= SDL_WINDOW_RESIZABLE;
#endif
		m_data->m_sdlWindow = SDL_CreateWindow(ci.m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ci.m_width, ci.m_height, flags);

		if (!m_data->m_sdlWindow)
		{
			const char* errStr = SDL_GetError();
			b3Assert(errStr != NULL);
			SDL_Quit();
			exit(EXIT_FAILURE);
		}

		m_data->m_sdlContext = SDL_GL_CreateContext((SDL_Window*)m_data->m_sdlWindow);
		SDL_GL_MakeCurrent(m_data->m_sdlWindow, m_data->m_sdlContext);
		SDL_SetWindowData(m_data->m_sdlWindow, "SDLOpenGLWindow", this);

#if defined(GLAD_GLES2)
		gladLoadGLES2((GLADloadfunc)SDL_GL_GetProcAddress);
#else
		gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
#endif

		SDL_GL_SetSwapInterval(0);  //1);
		SDL_GL_GetDrawableSize(m_data->m_sdlWindow, &m_data->m_width, &m_data->m_height);
		int windowWidth, windowHeight;
		SDL_GetWindowSize(m_data->m_sdlWindow, &windowWidth, &windowHeight);
		m_data->m_retinaScaleFactor = float(m_data->m_width) / float(windowWidth);
		glViewport(0, 0, m_data->m_width, m_data->m_height);
	}
}

void SDLOpenGLWindow::closeWindow()
{
	if (m_data->m_sdlWindow)
	{
		SDL_DestroyWindow(m_data->m_sdlWindow);
		SDL_Quit();
		m_data->m_sdlWindow = 0;
	}
}

void SDLOpenGLWindow::runMainLoop()
{
}

void SDLOpenGLWindow::pumpMessage()
{
	// Handle exit request
	if (requestedExit())
	{
		closeWindow();
		return;
	}		

	// Handle events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
			{
				setRequestExit();				
			}
			break;

			case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SDLSizeCallback(m_data->m_sdlWindow, event.window.data1, event.window.data2);
				}
			}
			break;

			case SDL_MOUSEWHEEL:
			{
				SDLScrollCallback(m_data->m_sdlWindow, event.wheel.x, event.wheel.y);
			}
			break;

			case SDL_MOUSEMOTION:
			{
				SDLCursorPosCallback(m_data->m_sdlWindow, event.motion.x, event.motion.y);
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			{
				const auto mods = SDL_GetModState();
				auto button = 0; // LEFT
				if (event.button.button == SDL_BUTTON_RIGHT)
					button = 1;  // RIGHT
				else if (event.button.button == SDL_BUTTON_MIDDLE)
					button = 2; // MIDDLE
				SDLMouseButtonCallback(m_data->m_sdlWindow, button, event.button.type, mods);
			}
			break;

			case SDL_FINGERMOTION:
			{
				int pos_x = (int)(event.tfinger.x * (float)m_data->m_width);
				int pos_y = (int)(event.tfinger.y * (float)m_data->m_height);
				if (pos_x < 0) pos_x = 0;
				if (pos_x > m_data->m_width - 1) pos_x = m_data->m_width - 1;
				if (pos_y < 0) pos_y = 0;
				if (pos_y > m_data->m_height - 1) pos_y = m_data->m_height - 1;

				SDLCursorPosCallback(m_data->m_sdlWindow, pos_x, pos_y);
			}
			break;

			case SDL_FINGERDOWN:
			{
				int pos_x = (int)(event.tfinger.x * (float)m_data->m_width);
				int pos_y = (int)(event.tfinger.y * (float)m_data->m_height);
				if (pos_x < 0) pos_x = 0;
				if (pos_x > m_data->m_width - 1) pos_x = m_data->m_width - 1;
				if (pos_y < 0) pos_y = 0;
				if (pos_y > m_data->m_height - 1) pos_y = m_data->m_height - 1;

				SDLCursorPosCallback(m_data->m_sdlWindow, pos_x, pos_y);
				SDLMouseButtonCallback(m_data->m_sdlWindow, SDL_BUTTON_LEFT, SDL_MOUSEBUTTONDOWN, 0);
			}
			break;

			case SDL_FINGERUP:
			{
				SDLMouseButtonCallback(m_data->m_sdlWindow, SDL_BUTTON_LEFT, SDL_MOUSEBUTTONUP, 0);
			}
			break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				auto mods = (int)SDL_GetModState();
				SDLKeyCallback(m_data->m_sdlWindow, event.key.keysym.sym, event.key.keysym.scancode, event.key.state, mods);
			}
			break;

			default:
				break;
		}
	}
}

float SDLOpenGLWindow::getTimeInSeconds()
{
	return 0.f;
}

bool SDLOpenGLWindow::requestedExit() const
{
	bool shouldClose = m_data->m_requestedExit;

	if (m_data->m_sdlWindow)
	{
		shouldClose = shouldClose;
	}
	return shouldClose;
}

void SDLOpenGLWindow::setRequestExit()
{
	m_data->m_requestedExit = true;
}

void SDLOpenGLWindow::startRendering()
{
	pumpMessage();

	if (m_data->m_sdlWindow)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
}

void SDLOpenGLWindow::endRendering()
{
	SDL_GL_SwapWindow(m_data->m_sdlWindow);
}

bool SDLOpenGLWindow::isModifierKeyPressed(int key)
{
	bool result = false;

	switch (key)
	{
		case B3G_SHIFT:
		{
			result = m_data->m_shiftPressed;
			break;
		}
		case B3G_ALT:
		{
			result = m_data->m_altPressed;
			break;
		}
		case B3G_CONTROL:
		{
			result = m_data->m_ctrlPressed;
			break;
		}
		default:
		{
		}
	}
	return result;
}

void SDLOpenGLWindow::setMouseMoveCallback(b3MouseMoveCallback mouseCallback)
{
	m_data->m_mouseMoveCallback = mouseCallback;
}

b3MouseMoveCallback SDLOpenGLWindow::getMouseMoveCallback()
{
	return m_data->m_mouseMoveCallback;
}

void SDLOpenGLWindow::setMouseButtonCallback(b3MouseButtonCallback mouseCallback)
{
	m_data->m_mouseButtonCallback = mouseCallback;
}

b3MouseButtonCallback SDLOpenGLWindow::getMouseButtonCallback()
{
	return m_data->m_mouseButtonCallback;
}

void SDLOpenGLWindow::setResizeCallback(b3ResizeCallback resizeCallback)
{
	m_data->m_resizeCallback = resizeCallback;
	getResizeCallback()(m_data->m_width / getRetinaScale(), m_data->m_height / getRetinaScale());
}

b3ResizeCallback SDLOpenGLWindow::getResizeCallback()
{
	return m_data->m_resizeCallback;
}

void SDLOpenGLWindow::setWheelCallback(b3WheelCallback wheelCallback)
{
	m_data->m_wheelCallback = wheelCallback;
}

b3WheelCallback SDLOpenGLWindow::getWheelCallback()
{
	return m_data->m_wheelCallback;
}

void SDLOpenGLWindow::setKeyboardCallback(b3KeyboardCallback keyboardCallback)
{
	m_data->m_keyboardCallback = keyboardCallback;
}

b3KeyboardCallback SDLOpenGLWindow::getKeyboardCallback()
{
	return m_data->m_keyboardCallback;
}

void SDLOpenGLWindow::setRenderCallback(b3RenderCallback renderCallback)
{
	m_data->m_renderCallback = renderCallback;
}

void SDLOpenGLWindow::setWindowTitle(const char* title)
{
	if (m_data->m_sdlWindow)
	{
		SDL_SetWindowTitle(m_data->m_sdlWindow, title);
	}
}

float SDLOpenGLWindow::getRetinaScale() const
{
	return m_data->m_retinaScaleFactor;
}
void SDLOpenGLWindow::setAllowRetina(bool allow)
{
}

int SDLOpenGLWindow::getWidth() const
{
	if (m_data->m_sdlWindow)
	{
		SDL_GL_GetDrawableSize(m_data->m_sdlWindow, &m_data->m_width, &m_data->m_height);
	}
	int width = m_data->m_width / m_data->m_retinaScaleFactor;
	return width;
}
int SDLOpenGLWindow::getHeight() const
{
	if (m_data->m_sdlWindow)
	{
		SDL_GL_GetDrawableSize(m_data->m_sdlWindow, &m_data->m_width, &m_data->m_height);
	}
	return m_data->m_height / m_data->m_retinaScaleFactor;
}

int SDLOpenGLWindow::fileOpenDialog(char* fileName, int maxFileNameLength)
{
	return 0;
}

#endif  //B3_USE_SDL
