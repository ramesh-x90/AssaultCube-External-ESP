#pragma once
#include "ProcessManager.h"




class WindowManager
{

private:
	static HWND handle;

	static ProcessManager * processManager;

	static WindowManager * instance;

	WindowManager(ProcessManager *pm);

	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);



public:
	WindowManager() = delete;

	~WindowManager();

	void setWindowHandle();

	HWND getWindowHandle();

	static WindowManager * create(ProcessManager* pm);

	static WindowManager* getInstance();

	RECT getWindowRect();


};

