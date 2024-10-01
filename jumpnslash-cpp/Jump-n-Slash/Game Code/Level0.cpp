#include "Level0.h"

#include "../Engine Code/GridManager.h"
#include "LevelMap.h"

#include "Player.h"

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
	pMap = new LevelMap(GridManager::GetGrid("test"));
	pPlayer = new Player(pMap->GetStartingSpawnPoint());
}

void Level0::End()
{
	delete pPlayer;
	pPlayer = nullptr;

	delete pMap;
	pMap = nullptr;
}
