#include "MapManager.h"

#include "LevelMap.h"

MapManager* MapManager::pInstance = nullptr;

MapManager& MapManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new MapManager();
	}
	return *pInstance;
}

void MapManager::LoadMap(std::string key, std::string filename)
{
	Instance().privLoadMap(key, filename);
}

void MapManager::privLoadMap(std::string key, std::string fileneame)
{
	assert(levelMaps.count(key) == 0); // no duplicate keys!

	levelMaps.emplace(key, new LevelMap(filename));
}
