#include "TilesetManager.h"

TilesetManager* TilesetManager::pInstance = nullptr;

TilesetManager& TilesetManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new TilesetManager();
	}
	return *pInstance;
}

void TilesetManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}
