#include "pch.h"
#include "ProcessManager.h"







ProcessManager::ProcessManager(const wchar_t* processName , const wchar_t* moduleName)
{
	this->processName = processName;
	this->moduleName = processName;

}


DWORD ProcessManager::getProcId()
{


	DWORD pId = 0;
	BOOL hResult;


	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (INVALID_HANDLE_VALUE == hSnapshot) return pId;

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);

	hResult = Process32First(hSnapshot, &pe);

	while (hResult)
	{
		if (!wcscmp(this->processName, pe.szExeFile))
		{
			pId = pe.th32ProcessID;
			break;
		}

		hResult = Process32Next(hSnapshot, &pe);
	}

	CloseHandle(hSnapshot);
	return pId;
}

uintptr_t ProcessManager::getModuleBaseAddress()
{

	if (baseAddress)
		return baseAddress;

	DWORD procID = getProcId();
	BOOL res;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (INVALID_HANDLE_VALUE == hSnapshot) return baseAddress;

	MODULEENTRY32 me;
	me.dwSize = sizeof(me);

	res = Module32First(hSnapshot, &me);

	while (res)
	{
		if (!wcscmp(me.szModule, moduleName))
		{
			baseAddress = (uintptr_t)me.modBaseAddr;
			break;
		}

		res = Module32Next(hSnapshot, &me);
	}
	CloseHandle(hSnapshot);

	return baseAddress;
}



const wchar_t* ProcessManager::getProcessName()
{
	return processName;
}

const wchar_t* ProcessManager::getModuleName()
{
	return moduleName;
}
