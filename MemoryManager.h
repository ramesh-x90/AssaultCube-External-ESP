#pragma once

#include "ProcessManager.h"


class MemoryManager
{
private:
	ProcessManager processManager;
	HANDLE hProc;

	static MemoryManager* instance;

	MemoryManager(ProcessManager pm);

public:
	
	MemoryManager() = delete;

	static MemoryManager* createInstance(ProcessManager pm);

	static MemoryManager* getInstance();


	uintptr_t findDynamicAddress(uintptr_t ptr, std::vector<unsigned int> offsets);

	BOOL ReadMemValue(uintptr_t ptr, void* des, int size);

	HANDLE getHandle();


	ProcessManager* getProcessManager();

	void Close();
};

