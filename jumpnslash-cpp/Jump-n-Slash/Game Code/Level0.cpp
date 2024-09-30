#include "Level0.h"

#include "Player.h"
#include "../Engine Code/LevelMap.h"

Level0::Level0()
	: pPlayer(nullptr),
	pMap(nullptr)
{
	// do nothing
}

Level0::~Level0()
{
	if (pPlayer != nullptr)
	{
		delete pPlayer;
	}
}

void Level0::Init()
{
	pPlayer = new Player();
	pMap = new LevelMap();
}

void Level0::End()
{
	delete pPlayer;
	pPlayer = nullptr;

	delete pMap;
	pMap = nullptr;
}
