#pragma once

#include "entityList.h"
#include "Graphics.h"
#include "MemoryManager.h"
#include "MvpMatrix.h"


class Esp
{

private:
	EntityList* _entityList;
	Graphics* _grahics;
	MemoryManager* _memoryManager ;
	MvpMatrix * _mvpMatrix;

public:
	Esp( EntityList * entityList , Graphics* grahics );
	
	~Esp();

	void drawPlayers(bool showTeam, bool showName, bool showDistence , bool showHealth);
	bool world2Screen(Vector3 pos, Vector3 * sPos);
	void setGraphics(Graphics* grahics);

	int getDistence(Vector3 lP, Vector3 eP);

	void drawHealthBar(Graphics* graphics, int health, float  phight, float x, float y);
};

