#include "pch.h"


#include "entityList.h"



EntityList* EntityList::instance;
Player * EntityList::_localPlayer;

EntityList::EntityList(MemoryManager mm, uintptr_t add) : address(add), memoryManager(mm)
{}



EntityList::~EntityList()
{
	delete instance;
}

void EntityList::populate(int entityCount)
{
	this->list.clear();

	unsigned int i = 0;

	while ( i < (unsigned)entityCount)
	{

		uintptr_t entAddress;
		memoryManager.ReadMemValue( this->address + 4 * i, (void*)&entAddress, sizeof(entAddress));
		i++;

		uintptr_t vTableAdd;
		BOOL s = memoryManager.ReadMemValue( entAddress, &vTableAdd, sizeof(vTableAdd));

		if ((vTableAdd == 0x4E4A98 || vTableAdd == 0x4E4AC0) && s)
		{
			addNewEntity(entAddress);

		}

	}

	std::cout << std::dec << "total " << list.size() << " players created" << std::endl;

}


void EntityList::addNewEntity(uintptr_t address)
{
	for (auto& ent : list)
	{
		if (ent.dmAddress == address) return;
	}
	
	this->list.push_back(Player(address));
}



EntityList * EntityList::createInstance(MemoryManager mm , uintptr_t address)
{
	if(instance == nullptr) instance = new EntityList(mm, address);
	return instance;
}

EntityList * EntityList::getInstance()
{
	return instance;
}

void EntityList::setAddress(uintptr_t address)
{
	this->address = address;
}


std::vector<Player> * EntityList::getPlayers()
{
	return &list;
}

int EntityList::getEnemyCount()
{
	assert(_localPlayer != nullptr);

	int count = 0;
	for (auto& ent : list)
	{
		if (ent.getTeamID() != _localPlayer->getTeamID())
			count++;
	}
	return count;
}

void EntityList::setLocalPlayer(Player* localPlayer)
{
	_localPlayer = localPlayer;
}

Player * EntityList::getLocalPlayer()
{
	return _localPlayer;
}



