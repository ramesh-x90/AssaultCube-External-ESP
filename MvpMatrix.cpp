#include "pch.h"
#include "MvpMatrix.h"



MvpMatrix::MvpMatrix(MemoryManager* mm)
{
	_memoryManager = mm;
}

bool MvpMatrix::getMvpMetrix( float * metrix)
{
	int sizeM = 16;



	return _memoryManager->ReadMemValue(
		_memoryManager->
		getProcessManager()->
		getModuleBaseAddress() + MVP_METRIX_OFFSET,
		metrix,
		sizeof(float) * sizeM
	
	);
}
