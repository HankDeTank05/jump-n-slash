#include "TilesetManager.h"

// engine includes
#include "Tileset.h"
#include "SpriteManager.h"

TilesetManager* TilesetManager::pInstance = nullptr;

TilesetManager& TilesetManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TilesetManager();
	}
	return *pInstance;
}

void TilesetManager::LoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<std::string> sprKeyList)
{
	Instance().privLoadTileset(tsKey, paletteNames, sprKeyList);
}

void TilesetManager::LoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<Sprite*> sprList)
{
	Instance().privLoadTileset(tsKey, paletteNames, sprList);
}

Tileset* TilesetManager::GetTileset(std::string tsKey)
{
	return Instance().privGetTileset(tsKey);
}

void TilesetManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void TilesetManager::privLoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<std::string> sprKeyList)
{
	assert(sets.count(tsKey) == 0); // invalid key! tileset key already exists

	std::list<Sprite*> sprList;

	for (std::list<std::string>::iterator it = sprKeyList.begin(); it != sprKeyList.end(); it++)
	{
		sprList.push_back(SpriteManager::GetSprite(*it));
	}

	Tileset* pSet = new Tileset(paletteNames, sprList);
	sets.emplace(tsKey, pSet);
}

void TilesetManager::privLoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<Sprite*> sprList)
{
	assert(sets.count(tsKey) == 0); // invalid key! tileset key already exists

	Tileset* pSet = new Tileset(paletteNames, sprList);
	sets.emplace(tsKey, pSet);
}

Tileset* TilesetManager::privGetTileset(std::string tsKey)
{
	assert(sets.count(tsKey) > 0); // invalid key! tileset key not found

	return sets.at(tsKey);
}
