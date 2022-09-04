#pragma once


#include "MemoryManager.h"



using String = std::string;

class Player
{
	private:

		unsigned int vTableOffset = 0x0;
		unsigned int vHeadOffset = 0x0004;
		unsigned int vPositionOffset = 0x0034;
		unsigned int viewAngel = 0x0040;
		unsigned int healthOffset = 0x00F8;
		unsigned int subWeponAmmoOffset = 0x0140;
		unsigned int mainWaponAmmoOffset = 0x0148;
		unsigned int nameOffset = 0x0225;
		unsigned int teamOffset = 0x32c;

		static MemoryManager * memoryManger;


	public:
		uintptr_t dmAddress;


		Player(uintptr_t dmAddress) ;

		~Player();


		static void setmemoryManger(MemoryManager * mm)
		{
			memoryManger = mm;
		}





		Vector3 getVhead();

		Vector3 getVposition();

		Vector2 getViewAngel();

		int getHealth();

		String getName();

		unsigned int getVtableAddress();

		int getTeamID();



};

