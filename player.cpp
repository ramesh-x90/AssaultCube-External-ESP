#include "pch.h"
#include "player.h"



MemoryManager * Player::memoryManger;

Player::Player(  uintptr_t dmAddress)
{

	if (memoryManger == nullptr)
	{
		MessageBox(NULL, L"memory manager not set in player class", L"ERROR!!", MB_OK);
		assert(0);
	}
	std::cout << "new player | address 0x" << std::hex << dmAddress  << std::dec << std::endl;
	this->dmAddress = dmAddress;
}



Player::~Player()
{}

Vector3 Player:: getVhead()
{
	Vector3 position;
	memoryManger->ReadMemValue(dmAddress + this->vHeadOffset , &position , sizeof(Vector3) );
	return position;
}

Vector3 Player::getVposition()
{
	Vector3 v;
	memoryManger->ReadMemValue( dmAddress + this->vPositionOffset, (void*)&v, sizeof(v));
	return v;
}

Vector2 Player::getViewAngel()
{
	Vector2 v;
	memoryManger->ReadMemValue( dmAddress + this->vHeadOffset, (void*)&v, sizeof(v));
	return v;
}


int Player:: getHealth()
{
	int health = 0;
	memoryManger->ReadMemValue( dmAddress + this->healthOffset, (void*)&health, sizeof(health));
	return health;
}

String Player::getName()
{
	char name[8];
	memoryManger->ReadMemValue( dmAddress + nameOffset, (void*)&name, sizeof(name) - 1);
	name[7] = '\0';
	return name;
}

unsigned int Player::getVtableAddress()
{
	unsigned int address;
	memoryManger->ReadMemValue( dmAddress + 0x0, (void*)&address, sizeof(address));
	return address;

}


int Player::getTeamID()
{
	int teamId;
	assert(memoryManger->ReadMemValue(dmAddress + teamOffset, (void*)&teamId, sizeof(teamId)));
	return teamId;
}

