// firstExternalTrainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ProcessManager.h"
#include "MemoryManager.h"
#include "player.h"

#include "entityList.h"
#include "WindowManager.h"
#include "OverlayWindow.h"



void espThreadFunc(WindowManager gameWindow);
Player findLocalPlayer(uintptr_t moduleBaseAdd, MemoryManager * mm);
EntityList* findEntityList(uintptr_t moduleBaseAdd, MemoryManager * mm);

using String = std::string ;


void espThreadFunc( WindowManager gameWindow)
{
	std::wstring overLayname = L"ESP-HACK";
	OverlayWindow hackOverlay(overLayname, gameWindow);
	hackOverlay.runEventLoop();
}



Player findLocalPlayer( uintptr_t moduleBaseAdd, MemoryManager * mm)
{
	uintptr_t dynamicPtrTolocalPlayer = moduleBaseAdd + PLAYER_OFFSET;

	uintptr_t playerAddr = 0;
	mm->ReadMemValue(dynamicPtrTolocalPlayer, &playerAddr , sizeof(playerAddr));

	if (!playerAddr)
	{
		std::cout << "Local player address not found";
		exit(-1);
	}

	std::cout << "player address found at 0x" << std::hex << playerAddr << std::dec << " (" << std::hex << dynamicPtrTolocalPlayer << std::dec << "-> )" << std::endl;


	Player localPlayer(playerAddr);

	return localPlayer;
}


EntityList * findEntityList(uintptr_t moduleBaseAdd, MemoryManager * mm)
{
	uintptr_t ptrToEntityList = moduleBaseAdd + ENTITY_LIST_OFFSET;
	uintptr_t entityListAddress = 0;
	
	if (!mm->ReadMemValue(ptrToEntityList, &entityListAddress, sizeof(entityListAddress)) || entityListAddress == 0)
	{
		std::cout << "entity list not found";
		exit(-1);
	}

	std::cout << "entity list found at 0x" << std::hex << entityListAddress << std::hex << std::endl;


	EntityList* entListInstance = EntityList::createInstance(*mm, entityListAddress);
	entListInstance->populate(100);


	return entListInstance;
}




int main()
{

	const wchar_t * name = L"ac_client.exe";
	std::vector<unsigned int> playerObjOffsets = { 0x0 };
	std::vector<unsigned int> entityListOffsets = { 0x0 };
	
	ProcessManager pm(name, name);

	MemoryManager * memoryManager = MemoryManager::createInstance(pm);

	Player::setmemoryManger(memoryManager);

	if (!pm.getProcId())
	{
		std::cout << "process not found" << std::endl;
		return 0;
	}


	uintptr_t moduleBaseAddress = pm.getModuleBaseAddress();
	std::cout << "module base address = " << "0x" << std::hex << moduleBaseAddress << std::endl;

	Player localPlayer = findLocalPlayer(moduleBaseAddress, memoryManager);

	EntityList* entitylistInstance = findEntityList(moduleBaseAddress, memoryManager);
	entitylistInstance->setLocalPlayer(&localPlayer);



	DWORD dwExit;
	

	std::cout << std::dec << "localPlayer Health = " << localPlayer.getHealth() << std::endl;
	std::cout << "localPlayer name = " << localPlayer.getName() << std::endl;

	WindowManager * gameWindow = WindowManager::create(&pm);


	std::thread espThread( &espThreadFunc ,  *gameWindow);

	int i = 0;
	while (GetExitCodeProcess( memoryManager->getHandle(), &dwExit) && dwExit == STILL_ACTIVE )
	{

		Sleep(1000);

	}


	espThread.join();

	memoryManager->Close();
	return 0;
}

