#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <array>
#include <list>

#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "../Engine Code/DrawableObject.h"

// forward declarations
class MapTile;

class LevelMap : public DrawableObject
{
public:
	LevelMap() = delete;
	LevelMap(std::vector<std::vector<std::string>>* grid);
	LevelMap(const LevelMap& lm) = delete;
	LevelMap& operator=(const LevelMap& lm) = delete;
	virtual ~LevelMap();

	virtual void Draw() override;

private:
	struct RoomData
	{
		sf::Vector2i origin;
		sf::Vector2i size;
		bool isStartingRoom;
		bool hasPlayerSpawn;
		sf::Vector2f* playerSpawnPoint; // if hasPlayerSpawn == false, this is nullptr
		std::list<sf::Vector2f> enemyLeftSpawns;
		std::list<sf::Vector2f> enemyRightSpawns;
	};

	using RoomList = std::list<RoomData*>;
public:
	using RoomListRef = RoomList::iterator;

private: // level map accessors. for selective access only (thru attorney)
	sf::Vector2f GetStartingSpawnPoint();

private:
	std::array<std::array<sf::Sprite*, MAX_LEVEL_SIZE>, MAX_LEVEL_SIZE> map;
	sf::Vector2i usedSize;
	RoomList rooms;
};

#endif