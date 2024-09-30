#include "LevelMap.h"

#include "JumpSlashEngine.h"
#include "SpriteManager.h"

LevelMap::LevelMap()
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (y == 0 || x == 0 || y == map.size() - 1 || x == map[y].size() - 1)
			{
				map[y][x] = SpriteManager::GetSprite("block solid");
			}
			else
			{
				map[y][x] = nullptr;
			}
		}
	}

	EnqueueForDrawRegistration();
}

LevelMap::LevelMap(std::string filename)
{
	assert(false);

	EnqueueForDrawRegistration();
}

LevelMap::~LevelMap()
{
	// do nothing
}

void LevelMap::Draw()
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] != nullptr)
			{
				map[y][x]->setPosition(x * 32.0f, y * 32.0f);
				JumpSlashEngine::GetWindow().draw(*map[y][x]);
			}
		}
	}
}
