#include "MapManager.h"

#include "LevelMap.h"

MapManager* MapManager::pInstance = nullptr;

MapManager::~MapManager()
{
	assert(false);
}

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

LevelMap* MapManager::GetMap(std::string key)
{
	return Instance().privGetMap(key);
}

void MapManager::privLoadMap(std::string key, std::string filename)
{
	assert(levelMaps.count(key) == 0); // no duplicate keys!

	LevelMap* pMap = new LevelMap(FOLDER_NAME + filename); // this line is left separate from the emplace call for easier debugging

	levelMaps.emplace(key, pMap);
}

LevelMap* MapManager::privGetMap(std::string key)
{
	assert(levelMaps.count(key) > 0); // if you triggered this assert, your key does not exist in map!

	return levelMaps.at(key);
}
