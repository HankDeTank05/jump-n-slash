#include "LevelMap.h"

#include <string>
#include <vector>

#include "../Engine Code/JumpSlashEngine.h"
#include "../Engine Code/SpriteManager.h"

//LevelMap::LevelMap()
//{
//	for (int y = 0; y < map.size(); y++)
//	{
//		for (int x = 0; x < map[y].size(); x++)
//		{
//			if (y == 0 || x == 0 || y == map.size() - 1 || x == map[y].size() - 1)
//			{
//				map[y][x] = SpriteManager::GetSprite("block solid");
//			}
//			else
//			{
//				map[y][x] = nullptr;
//			}
//		}
//	}
//
//	EnqueueForDrawRegistration();
//}

LevelMap::LevelMap(std::vector<std::vector<std::string>>* grid)
	: map(),
	usedSize(0, 0),
	rooms()
{
	// convert the grid into an array of sprite pointers
	for (int y = 0; y < grid->size(); y++)
	{
		assert(y < MAX_LEVEL_SIZE);

		for (int x = 0; x < grid->at(y).size(); x++)
		{
			assert(x < MAX_LEVEL_SIZE);
			std::string tileID = grid->at(y)[x];

			// empty space
			if(tileID == "00")
			{
				map[y][x] = nullptr;
			}
			// block solid
			else if (tileID == "03")
			{
				map[y][x] = SpriteManager::GetSprite("block solid");
			}
			// indicator room height
			else if (tileID == "04")
			{
				map[y][x] = SpriteManager::GetSprite("indicator room height");
			}
			// indicator room origin
			else if (tileID == "05") 
			{
				map[y][x] = SpriteManager::GetSprite("indicator room origin");
			}
			// indicator room origin start
			else if (tileID == "06")
			{
				map[y][x] = SpriteManager::GetSprite("indicator room origin start");
			}
			// indicator room width
			else if (tileID == "07") 
			{
				map[y][x] = SpriteManager::GetSprite("indicator room width");
			}
			// indicator spawn player right
			else if (tileID == "11")
			{
				map[y][x] = SpriteManager::GetSprite("indicator spawn player right");
			}
			// crash if the tileID can't be converted to an actual tile
			else 
			{
				assert(false);
			}

			// adjust the used size
			if (x > usedSize.x)
			{
				usedSize.x = x;
			}
		}
		// adjust the used size
		if (y > usedSize.y)
		{
			usedSize.y = y;
		}
	}

	// make it so these are actual sizes, not max indices (makes it easy for looping)
	usedSize.x += 1;
	usedSize.y += 1;

	// read the grid to create room data
	int y = 0;
	while (y < usedSize.y)
	{
		int x = 0;
		while (x < usedSize.x)
		{
			sf::Sprite* pStartOrigin = SpriteManager::GetSprite("indicator room origin start");
			sf::Sprite* pOrigin = SpriteManager::GetSprite("indicator room origin");
			sf::Sprite* pWidth = SpriteManager::GetSprite("indicator room width");
			sf::Sprite* pHeight = SpriteManager::GetSprite("indicator room width");

			if (map[y][x] == pOrigin || map[y][x] == pStartOrigin)
			{
				// iterate right until a width indicator is found or we go out of used or max bounds

				// iterate down until a height indicator is found or we go out of used or max bounds

				// NOTE: try storing indicator locations (and searching thru them) instead of doing this iteration?
			}

			x++;
		}

		y++;
	}

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
