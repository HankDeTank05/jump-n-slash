#include "LevelMap.h"

#include <string>
#include <vector>

#include "../Engine Code/JumpSlashEngine.h"
#include "../Engine Code/SpriteManager.h"

#include "BlockBreakable.h"
#include "BlockHazard.h"
#include "BlockSolid.h"
#include "PlatformSemisolid.h"
#include "Constants.h"

LevelMap::LevelMap(std::vector<std::vector<std::string>>* grid)
	: map(),
	usedSize(0, 0),
	rooms()
{
	std::map<std::string, std::list<sf::Vector2i>> tiles;

	// convert the grid into an array of LevelTile pointers
	for (int y = 0; y < grid->size(); y++)
	{
		assert(y < MAX_LEVEL_SIZE);

		for (int x = 0; x < grid->at(y).size(); x++)
		{
			assert(x < MAX_LEVEL_SIZE);
			std::string tileID = grid->at(y)[x];

			// add the indicator to the std::map

			std::string key = "not set";
			sf::Vector2i coords(x, y);

			// TODO: I hate that this is hard coded. replace this when json parsing is working
			
			// a position vector to pass to the LevelTiles
			sf::Vector2f worldPos(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));

			// empty space
			if(tileID == "00")
			{
				map[y][x] = nullptr;
				key = "empty";
			}
			// block breakable
			else if (tileID == "01")
			{
				map[y][x] = new BlockBreakable(worldPos);
				key = KEY_BLOCK_BREAKABLE;
			}
			// block hazard
			else if (tileID == "02")
			{
				map[y][x] = new BlockHazard(worldPos);
				key = KEY_BLOCK_HAZARD;
			}
			// block solid
			else if (tileID == "03")
			{
				map[y][x] = new BlockSolid(worldPos);
				key = KEY_BLOCK_SOLID;
			}
			// indicator room height
			else if (tileID == "04")
			{
				map[y][x] = new BlockSolid(worldPos); // TODO: make some formal definition for this replacement
				key = KEY_INDICATOR_ROOM_HEIGHT;
			}
			// indicator room origin
			else if (tileID == "05") 
			{
				map[y][x] = new BlockSolid(worldPos);
				key = KEY_INDICATOR_ROOM_ORIGIN;
			}
			// indicator room origin start
			else if (tileID == "06")
			{
				map[y][x] = new BlockSolid(worldPos);
				key = KEY_INDICATOR_ROOM_ORIGIN_START;
			}
			// indicator room width
			else if (tileID == "07") 
			{
				map[y][x] = new BlockSolid(worldPos);
				key = KEY_INDICATOR_ROOM_WIDTH;
			}
			// indicator spawn enemy left
			else if (tileID == "08")
			{
				map[y][x] = nullptr; // TODO: make some formal definition for this replacement
				key = KEY_INDICATOR_SPAWN_ENEMY_LEFT;
			}
			// indicator spawn enemy right
			else if (tileID == "09")
			{
				map[y][x] = nullptr;
				key = KEY_INDICATOR_SPAWN_ENEMY_RIGHT;
			}
			// indicator spawn player left
			else if (tileID == "10")
			{
				map[y][x] = nullptr;
				key = KEY_INDICATOR_SPAWN_PLAYER_LEFT;
			}
			// indicator spawn player right
			else if (tileID == "11")
			{
				map[y][x] = nullptr;
				key = KEY_INDICATOR_SPAWN_PLAYER_RIGHT;
			}
			// crash if the tileID can't be converted to an actual tile
			else 
			{
				assert(false);
			}

			// add the tile to the std::map
			if (tiles.count(key) == 0)
			{
				// create an empty std::list at the given key if it doesn't already exist
				tiles.emplace(key, std::list<sf::Vector2i>());
			}
			tiles.at(key).push_back(coords);

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

	// if you triggered this assert, you have more than one starting room in your level map
	assert(tiles.at(KEY_INDICATOR_ROOM_ORIGIN_START).size() == 1);
	sf::Vector2i startOrigin = tiles.at(KEY_INDICATOR_ROOM_ORIGIN_START).front();

	// make it so these are actual sizes, not max indices (makes it easy for looping)
	usedSize.x += 1;
	usedSize.y += 1;

	// use indicators to create room data (one room per origin indicator)

	std::list<sf::Vector2i> list = tiles.at(KEY_INDICATOR_ROOM_ORIGIN);
	list.push_front(tiles.at(KEY_INDICATOR_ROOM_ORIGIN_START).front());
	for (std::list<sf::Vector2i>::iterator it = list.begin(); it != list.end(); it++)
	{
		// determine the origin of the room
		sf::Vector2i origin = (*it);

		// search for the closest width indicator with the same y-value
		sf::Vector2i widthPos;
		std::list<sf::Vector2i> searchList = tiles.at("indicator room width");
		int minX = MAX_LEVEL_SIZE;
		for (std::list<sf::Vector2i>::iterator searchIt = searchList.begin(); searchIt != searchList.end(); searchIt++)
		{
			if ((*searchIt).y == origin.y && // the width indicator must have the same height (y-value)
				(*searchIt).x < minX && // make sure we're getting the closest one
				(*searchIt).x > origin.x) // but also make sure it is to the right of the origin tile
			{
				minX = (*searchIt).x;
				widthPos = *searchIt;
			}
		}
		// sanity check
		assert(origin.x < widthPos.x);

		// search for the closests height indicator with the same y-value
		sf::Vector2i heightPos;
		searchList = tiles.at("indicator room height");
		int minY = MAX_LEVEL_SIZE;
		for (std::list<sf::Vector2i>::iterator searchIt = searchList.begin(); searchIt != searchList.end(); searchIt++)
		{
			if ((*searchIt).x == origin.x && // the height indicator must have the same x-value
				(*searchIt).y < minY && // make sure we're getting the closest one
				(*searchIt).y > origin.y) // but also make sure it is below the origin tile
			{
				minY = (*searchIt).y;
				heightPos = *searchIt;
			}
		}
		// sanity check
		assert(origin.y < heightPos.y);

		// add any player spawns to the room
		searchList = std::list<sf::Vector2i>();
		if (tiles.count("indicator spawn player left") > 0)
		{
			searchList.splice(searchList.end(), tiles.at("indicator spawn player left"));
		}
		if (tiles.count("indicator spawn player right") > 0)
		{
			searchList.splice(searchList.end(), tiles.at("indicator spawn player right"));
		}
		sf::Vector2i playerSpawn(-1, -1);
		for (std::list<sf::Vector2i>::iterator searchIt = searchList.begin(); searchIt != searchList.end(); searchIt++)
		{
			if (origin.x <= (*searchIt).x && (*searchIt).x <= widthPos.x &&
				origin.y <= (*searchIt).y && (*searchIt).y <= heightPos.y)
			{
				// if this assert gets triggered, you have more than one player spawn in your room
				assert(playerSpawn.x == -1 && playerSpawn.y == -1);
				playerSpawn = (*searchIt);
			}
		}

		// set all the room data
		RoomData* pRoomData = new RoomData();
		pRoomData->origin = sf::Vector2f(origin.x * TILE_SIZE_F, origin.y * TILE_SIZE_F);
		pRoomData->size = sf::Vector2f((widthPos.x - origin.x) * TILE_SIZE_F, (heightPos.y - origin.y) * TILE_SIZE_F);
		pRoomData->isStartingRoom = origin == startOrigin;
		pRoomData->hasPlayerSpawn = playerSpawn.x >= 0 && playerSpawn.y >= 0;
		if (pRoomData->hasPlayerSpawn)
		{
			pRoomData->playerSpawnPoint = new sf::Vector2f(playerSpawn.x * TILE_SIZE_F, playerSpawn.y * TILE_SIZE_F);
		}
		else
		{
			pRoomData->playerSpawnPoint = nullptr;
		}
		pRoomData->enemyLeftSpawns = std::list<sf::Vector2f>(); // finish this line
		pRoomData->enemyRightSpawns = std::list<sf::Vector2f>(); // finish this line

		// add any enemy spawns to the room
		if (tiles.count("indicator spawn enemy left") > 0)
		{
			searchList = tiles.at("indicator spawn enemy left");
			for (std::list<sf::Vector2i>::iterator searchIt = searchList.begin(); searchIt != searchList.end(); searchIt++)
			{
				if (origin.x <= (*searchIt).x && (*searchIt).x <= widthPos.x &&
					origin.y <= (*searchIt).y && (*searchIt).y <= heightPos.y)
				{
					pRoomData->enemyLeftSpawns.push_back(sf::Vector2f(static_cast<float>((*searchIt).x), static_cast<float>((*searchIt).y)));
				}
			}
		}
		if (tiles.count("indicator spawn enemy right") > 0)
		{
			searchList = tiles.at("indicator spawn enemy right");
			for (std::list<sf::Vector2i>::iterator searchIt = searchList.begin(); searchIt != searchList.end(); searchIt++)
			{
				if (origin.x <= (*searchIt).x && (*searchIt).x <= widthPos.x &&
					origin.y <= (*searchIt).y && (*searchIt).y <= heightPos.y)
				{
					pRoomData->enemyRightSpawns.push_back(sf::Vector2f(static_cast<float>((*searchIt).x), static_cast<float>((*searchIt).y)));
				}
			}
		}
		
		// add the created room data to the list
		rooms.push_back(pRoomData);

		// sanity check to make sure there's only one starting room
		int startRoomCount = 0;
		for (RoomList::iterator it = rooms.begin(); it != rooms.end(); it++)
		{
			if ((*it)->isStartingRoom == true)
			{
				startRoomCount++;
			}
		}
		assert(startRoomCount == 1);
		assert(rooms.front()->isStartingRoom == true); // the starting room should always be the first one in the list
	}
}

LevelMap::~LevelMap()
{
	// delete owned pointers in room data
	for (std::list<RoomData*>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		RoomData* pRoomData = (*it);
		if (pRoomData->playerSpawnPoint != nullptr)
		{
			delete pRoomData->playerSpawnPoint;
		}
		delete pRoomData;
	}

	// delete owned pointers in the levelmap
	for (std::array<std::array<LevelTile*, MAX_LEVEL_SIZE>, MAX_LEVEL_SIZE>::iterator yIt = map.begin(); yIt != map.end(); yIt++)
	{
		std::array<LevelTile*, MAX_LEVEL_SIZE> row = *yIt;
		for (std::array<LevelTile*, MAX_LEVEL_SIZE>::iterator xIt = row.begin(); xIt != row.end(); xIt++)
		{
			if (*xIt != nullptr)
			{
				delete (*xIt);
			}
		}
	}
}

sf::Vector2f LevelMap::GetStartingSpawnPoint()
{
	assert(rooms.front()->isStartingRoom == true);
	assert(rooms.front()->playerSpawnPoint != nullptr);
	return *(rooms.front()->playerSpawnPoint);
}

LevelTile* LevelMap::GetTileAtPos(sf::Vector2f worldPos)
{
	int x = static_cast<int>(worldPos.x / TILE_SIZE_F);
	int y = static_cast<int>(worldPos.y / TILE_SIZE_F);

	assert(0 <= x);
	assert(x < MAX_LEVEL_SIZE);
	assert(0 <= y);
	assert(y < MAX_LEVEL_SIZE);

	return map[y][x];
}
