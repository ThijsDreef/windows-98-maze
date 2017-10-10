#include "Window.h"

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool Window::initGL()
{
	glewInit();
	glShadeModel(GL_SMOOTH);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearDepth(1.0f);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	std::cout << glGetString(GL_VERSION) << "glVersion";
	return true;
}
void Window::RequestRender(Object * renderMethod)
{
	renderQue.push_back(renderMethod);
}
void Window::preRender()
{
	if (currentShader != renderQue[renderedObjects]->shader)
	{
		glFinish();
		currentShader = renderQue[renderedObjects]->shader;
		GraphicResourceManagement::getInstance()->requestShaderChange(currentShader);
	}
	renderQue.at(renderedObjects)->renderRequest();
	renderedObjects++;	
}
void Window::WindowHandler()
{
	//ShowCursor(false);

	MSG msg;
	ShowCursor(false);
	update = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (update)
			{
				if (active)
				{
					RECT * temp = new RECT;
					GetWindowRect(hWnd, temp);
					SetCursorPos(temp->left + windowWidth / 2, temp->top + windowHeight / 2);
					keyHandler->handleMessage(mvmsg);

				}
				updateWindow(true);
			}
			else if (renderedObjects < renderQue.size())
			{
				//preRender();
			}
		}

	}
	renderQue.clear();
	delete GraphicResourceManagement::getInstance();
	delete this;
}
void Window::updateWindow(bool clear)
{
	glFinish();
	SwapBuffers(getWindowContent());
	if (clear)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	std::vector<std::vector<Object *>> temp;
	int found;
	for (int i = renderedObjects; i < renderQue.size(); i++)
	{
		found = -1;
		for (int j = 0; j < temp.size(); j++)
		{
			if (renderQue[i]->shader == temp[j][0]->shader)
				found = j;
		}
		if (found < temp.size())
			temp.at(found).push_back(renderQue[i]);
		else
		{
			std::vector<Object*> newObject;
			newObject.push_back(renderQue.at(i));
			temp.push_back(newObject);
		}

	}

	for (int i = 0; i < temp.size(); i++)
	{
		GraphicResourceManagement::getInstance()->requestShaderChange(temp[i][0]->shader);
		currentShader = temp[i][0]->shader;
		for (int j = 0; j < temp[i].size(); j++)
		{
			temp[i][j]->renderRequest();
		}
	}
	renderedObjects = 0;
	renderQue.clear();

	update = false;
}
void Window::resize(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
}
bool Window::createGlWindow(char* title, int width, int height, int bits, bool fullscreen, SystemObject * keyHandler)
{
	this->keyHandler = keyHandler;
	msg = new KeyMessage(0, true);
	mvmsg = new MouseVelocityMessage(0, 0, 0, 0);
	//std::cout << GL_VERSION;
	windowWidth = width;
	windowHeight = height;

	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;

	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	this->fullscreen = fullscreen;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = this->WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "opengl";

	if (!RegisterClass(&wc))
	{
		MessageBoxA(NULL, "failed to register window class", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (fullscreen)
	{
		DEVMODEA dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		if (ChangeDisplaySettingsA(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBoxA(NULL, "the requested fullscreen mode is not supported by \n your video card. use windowed mode instead?", "opengl application", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBoxA(NULL, "the application will now close", "opengl application", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);
	if (!(hWnd = CreateWindowExA(dwExStyle, "opengl", title, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, hInstance, NULL)))
	{
		killWindow();
		MessageBoxA(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	SetPropA(hWnd, "opengl", this);
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//version number
		PFD_DRAW_TO_WINDOW |	//format must support window
		PFD_SUPPORT_OPENGL |	//format must support opengl
		PFD_DOUBLEBUFFER,		//must support dubble buffering
		PFD_TYPE_RGBA,			// request an rgba format
		bits,					//select color depth 
		0, 0, 0, 0, 0, 0,       //color bits ignored
		0,						//no alpha  buffer
		0,						//shift bit ignored
		0,						//no accumulation buffer
		0, 0, 0, 0,				//accumulation bits ignored
		16,						//16bit Z-Buffer (depth Buffer)
		0,						//no stencil buffer
		0,						//no Auxilliary buffer
		PFD_MAIN_PLANE,         //main drawing layer
		0,						//reserved
		0, 0, 0					//layer masks ignored
	};
	if (!(hDC = GetDC(hWnd)))
	{
		killWindow();
		MessageBoxA(NULL, "cant create a GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		killWindow();
		MessageBoxA(NULL, "cant find a suitable pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		killWindow();
		MessageBoxA(NULL, "cant set the pixelformat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!(hRC = wglCreateContext(hDC)))
	{
		killWindow();
		MessageBoxA(NULL, "cant create a GL rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (!wglMakeCurrent(hDC, hRC))
	{
		killWindow();
		MessageBoxA(NULL, "can't activate the gl rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	resize(width, height);
	if (!initGL())
	{
		killWindow();
		MessageBoxA(NULL, "initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	WindowHandler();
	return true;
}
HDC Window::getWindowContent()
{
	return hDC;
}
void Window::killWindow()
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBoxA(NULL, "Release of DC and RC failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))
		{
			MessageBoxA(NULL, "release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK);
		}
		hRC = NULL;
	}
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBoxA(NULL, "release device context failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBoxA(NULL, "destroying window failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}
	if (!UnregisterClassA("opengl", hInstance))
	{
		MessageBoxA(NULL, "error unregistering class", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* pThis = static_cast<Window*>(GetPropA(hWnd, "opengl"));
	if (pThis)
		return pThis->realWndProc(hWnd, uMsg, wParam, lParam);
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK Window::realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SETFOCUS:
		{
			active = true;
			break;
		}
		case WM_KILLFOCUS:
		{
			active = false;
			break;
		}
		case WM_SYSCOMMAND:
		{
			switch (wParam)
			{
			case SC_SCREENSAVE:
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
		case WM_CLOSE:
		{
			// to do fix this to a keyHandler
			MessageHandler::postSystemMessage(new Message(QUIT));
			return 0;
		}
		case WM_KEYDOWN:
		{
			msg->key = wParam;
			msg->down = true;
			keyHandler->handleMessage(msg);
			return 0;
		}
		case WM_KEYUP:
		{
			msg->key = wParam;
			msg->down = false;
			keyHandler->handleMessage(msg);
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			RECT * rect = new RECT;
			GetWindowRect(hWnd, rect);
			POINTS temp = MAKEPOINTS(lParam);
			int offx = (fullscreen) ? 0 : 8;
			int offy = (fullscreen) ? 0 : 31;
			mvmsg->xvel = ((float) (temp.x+ offx) / windowWidth) - 0.5f;
			mvmsg->yvel = (1 - (float)(temp.y + offy)/ windowHeight) - 0.5f;
			mvmsg->mouseX = temp.x;
			mvmsg->mouseY = temp.y;
			//SetCursorPos(temp->left + windowWidth / 2, temp->top + windowHeight / 2);
			return 0;
		}
		case WM_SIZE:
		{
			resize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
		case WM_SIZING:
		{
			resize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}