#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <array>

#include <SFML/Graphics.hpp>

#include "DrawableObject.h"
#include "../Game Code/Constants.h"

// forward declarations
class MapTile;

class LevelMap : public DrawableObject
{
public:
	LevelMap() = delete;
	LevelMap(std::string filename);
	LevelMap(const LevelMap& lm) = delete;
	LevelMap& operator=(const LevelMap& lm) = delete;
	virtual ~LevelMap();

	virtual void Draw() override;

private:
	std::array<std::array<sf::Sprite*, MAX_LEVEL_SIZE>, MAX_LEVEL_SIZE> map;
};

#endif