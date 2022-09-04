#include "pch.h"
#include "WindowManager.h"


WindowManager* WindowManager::instance;
HWND WindowManager::handle;
ProcessManager* WindowManager::processManager;

WindowManager::WindowManager(ProcessManager* pm)
{
	processManager = pm;
	setWindowHandle();
}

WindowManager::~WindowManager()
{
	//CloseHandle(*handle);
}

void WindowManager::setWindowHandle()
{
	
	if(handle == nullptr) EnumWindows(EnumWindowsProc, NULL);
	
}

HWND WindowManager::getWindowHandle()
{

	return instance->handle;
}

WindowManager * WindowManager::create(ProcessManager *pm)
{

	instance = new WindowManager(pm);
	return instance;

}


WindowManager* WindowManager::getInstance()
{
	return instance;
}


BOOL CALLBACK WindowManager::EnumWindowsProc(
	_In_ HWND   hwnd,
	_In_ LPARAM lParam)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	if (pid == processManager->getProcId())
	{
		instance->handle = hwnd;
		return false;
	}

	return true;
}


RECT WindowManager::getWindowRect()
{
	RECT sRect , pRect;
	GetClientRect(handle, &sRect);
	GetWindowRect(handle, &pRect);

	pRect.top = pRect.bottom - sRect.bottom;

	return pRect;
}

