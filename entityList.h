#pragma once

#include "player.h"
#include "MemoryManager.h"




class EntityList
{
private:

	static EntityList* instance;
	MemoryManager memoryManager;

	static Player * _localPlayer;

private:
	std::vector<Player> list;
	EntityList(MemoryManager mm, uintptr_t address);
	void addNewEntity(uintptr_t address);


public:
	uintptr_t address;

public:
	EntityList() = delete;
	~EntityList();

	void setAddress(uintptr_t address);

	void populate(int entityCount);



	static EntityList * createInstance(MemoryManager mm, uintptr_t address);

	static EntityList * getInstance();

	std::vector<Player> * getPlayers();

	int getEnemyCount();

	void setLocalPlayer(Player * localPlayer);

	static Player * getLocalPlayer();



};