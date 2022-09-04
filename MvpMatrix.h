#pragma once

#include "MemoryManager.h"

class MvpMatrix
{

private:
	MemoryManager * _memoryManager;
	uintptr_t _address;
public:
	MvpMatrix(MemoryManager * mm );

	bool getMvpMetrix(float* metrix);
};

