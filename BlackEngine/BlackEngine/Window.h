#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
#include <WinUser.h>
#include <include\GL\glew.h>
#include "GraphicResourceManagement.h"
#include "MessageHandler.h"
class Window
{
private:
	std::vector<Object*> renderQue;
	int renderedObjects = 0;
	std::string currentShader;
	bool moved = false;
	int windowWidth = 0;
	int windowHeight = 0;
	SystemObject * keyHandler;
	KeyMessage * msg;
	MouseVelocityMessage * mvmsg;
	SHORT max = 0;
public:
	void preRender();
	void RequestRender(Object* renderMethod);
	bool update = false;
	bool done = false;
	HGLRC hRC = NULL;
	HDC hDC = NULL;
	HWND hWnd = NULL;
	HINSTANCE hInstance;
	void updateWindow(bool clear);
	bool active = true;
	bool fullscreen = true;
	void resize(GLsizei width, GLsizei height);
	bool initGL();
	void killWindow();
	bool createGlWindow(char* title, int width, int height, int bits, bool fullscreen, SystemObject * keyHandler);
	HDC getWindowContent();
	void WindowHandler();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK realWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};