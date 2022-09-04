#include "pch.h"
#include "Esp.h"


#define MAX_HEALTH 100

Esp::Esp( EntityList* entityList, Graphics * grahics )
{
	this->_entityList = entityList;
	this->_grahics = grahics;
	_memoryManager = MemoryManager::getInstance();

	_mvpMatrix = new MvpMatrix(_memoryManager);

}

void Esp::setGraphics(Graphics * grahics)
{
	this->_grahics = grahics;
}

Esp::~Esp()
{
	delete _mvpMatrix;
}

void Esp::drawPlayers(bool showTeam , bool showName , bool showDistence , bool showHealth)
{
	for ( int i = 0 ; i < (int) _entityList->getPlayers()->size(); i++)
	{

		Player ent = _entityList->getPlayers()->at(i);
		int health = ent.getHealth();

		if (health > 0 && health <= 100)
		{
			Vector3 hVec, pVec = { 0,0,0 };


			if (!(world2Screen(ent.getVhead(), &hVec) && world2Screen(ent.getVposition(), &pVec)))
				continue;

			int dis = getDistence(_entityList->getLocalPlayer()->getVposition(), ent.getVposition());

			String name = ent.getName();

			String sHealth = std::to_string(health);
			String sdis = std::to_string(dis);

			int boxHight = (int)(pVec.y - hVec.y);
			int boxWidth = (int)(boxHight / 2);

			if (boxWidth > 200)
				boxWidth = 200;

			D3DCOLOR color;

			if (_entityList->getLocalPlayer()->getTeamID() == ent.getTeamID())
			{
				if (!showTeam)
					continue;
				color = WHITE;
			}
			else
			{
				color = RED;
			}

			//_grahics->drawText((char*)name.c_str(), hVec.x - boxWidth / 2, hVec.y - 13, color);
			//_grahics->drawText((char*)sHealth.c_str(), pVec.x - boxWidth / 2, pVec.y + 5, color);
			_grahics->drawText((char*)sdis.c_str(), pVec.x - boxWidth / 2, pVec.y + 13, color);
			_grahics->DrawBox(hVec.x - boxWidth / 2, hVec.y, boxWidth, boxHight, 1, color);

			if (showHealth)
				drawHealthBar(_grahics, health, boxHight, hVec.x - boxWidth / 2 - 2, hVec.y);
		}
	
	}

}


void Esp::drawHealthBar(Graphics * graphics , int health , float  phight , float x , float y)
{
	float gonehealth = MAX_HEALTH - health;

	float scaledHealth = std::ceil(gonehealth / MAX_HEALTH *  phight);

	graphics->DrawLine(x, y, x, y + phight, RED, 3);
	graphics->DrawLine(x, y + scaledHealth, x, y + phight, GREEN, 3);
}

bool Esp::world2Screen(Vector3 pos , Vector3 * sPos)
{
	ClipCOORD clipCoords{0,0,0,0};
	Vector3 NDC{ 0,0,0 };

	float mX = (float)_grahics->overlayWindowWidth /2.0f;
	float mY = (float)_grahics->overlayWindowHeight / 2.0f;

	float mvpMetrix[16];
	if (_mvpMatrix->getMvpMetrix(mvpMetrix))
	{
		clipCoords.x = pos.x * mvpMetrix[0] + pos.y * mvpMetrix[4] + pos.z * mvpMetrix[8] + mvpMetrix[12];
		clipCoords.y = pos.x * mvpMetrix[1] + pos.y * mvpMetrix[5] + pos.z * mvpMetrix[9]  + mvpMetrix[13];
		clipCoords.z = pos.x * mvpMetrix[2] + pos.y * mvpMetrix[6] + pos.z * mvpMetrix[10] + mvpMetrix[14];
		clipCoords.w = pos.x * mvpMetrix[3] + pos.y * mvpMetrix[7] + pos.z * mvpMetrix[11] + mvpMetrix[15];
	}

	if (clipCoords.z < 0.1f)
		return false;

	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;


	sPos->x = (512 + NDC.x) + (512 * NDC.x) + 5 ;
	sPos->y = (384 + NDC.y) - (384 * NDC.y) - 16;


	return true;
}


int Esp::getDistence(Vector3 lP , Vector3 eP)
{
	return ceil(
		sqrt(
			std::pow(lP.x - eP.x, 2) + std::pow(lP.y - eP.y, 2) + std::pow(lP.z - eP.z, 2)
		)
	);
}
