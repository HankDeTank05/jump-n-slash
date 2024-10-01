#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <array>

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
		bool hasSpawn;
		sf::Vector2i* spawnPoint;
	};

private:
	std::array<std::array<sf::Sprite*, MAX_LEVEL_SIZE>, MAX_LEVEL_SIZE> map;
	sf::Vector2i usedSize;
	std::array<RoomData*, 50> rooms;
};

#endif