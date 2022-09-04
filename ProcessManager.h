#pragma once
class ProcessManager
{

private:
	const wchar_t* processName; 
	const wchar_t*  moduleName;
	uintptr_t baseAddress = 0;


	

public:
	ProcessManager(const wchar_t* processName,const wchar_t* moduleName);


	DWORD getProcId();

	uintptr_t getModuleBaseAddress();

	const wchar_t* getProcessName();
	const wchar_t* getModuleName();
};

