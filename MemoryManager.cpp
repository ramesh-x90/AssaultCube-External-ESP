#include "pch.h"

#include "MemoryManager.h"



MemoryManager* MemoryManager::instance;
MemoryManager::MemoryManager(ProcessManager pm) : processManager(pm)
{
	this->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, pm.getProcId());
	instance = this;
}

void MemoryManager::Close()
{
	CloseHandle(hProc);
	delete instance;
}

MemoryManager * MemoryManager::createInstance(ProcessManager pm)
{
	if(instance)
		return instance;
	instance = new MemoryManager(pm);
}

uintptr_t MemoryManager::findDynamicAddress( uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;

	for (auto& offset : offsets)
	{
		ReadProcessMemory(hProc, (void*)addr, &addr, sizeof(addr), nullptr);
		addr += offset;

	}

	return addr;
}


BOOL MemoryManager::ReadMemValue(uintptr_t ptr, void* des, int size)
{
	return ReadProcessMemory(hProc, (void*)ptr, des, size, nullptr);
}



HANDLE MemoryManager::getHandle()
{
	return hProc;
}


MemoryManager* MemoryManager::getInstance()
{
	return instance;
}

ProcessManager* MemoryManager::getProcessManager()
{
	return &processManager;
}
