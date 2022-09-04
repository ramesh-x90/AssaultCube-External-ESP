#pragma once

#include "Graphics.h"
#include "WindowManager.h"


class OverlayWindow
{
private:
	HINSTANCE hInstance;
	std::wstring overlayWindowName;
	HWND cWinHandle;
	

	WindowManager gameWindowManager;

	ATOM registerClass();

	void createWindow();




public:

	OverlayWindow(std::wstring name , WindowManager gWm);

	~OverlayWindow();

	HWND getOverlayHandle();

	void adjestWindow();

	void runEventLoop();

	WINDOW getWindowAttribute();


};

