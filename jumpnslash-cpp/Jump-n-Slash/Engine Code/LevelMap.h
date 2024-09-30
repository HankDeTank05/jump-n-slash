#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include <array>

#include <SFML/Graphics.hpp>

#include "DrawableObject.h"

// forward declarations
class MapTile;

class LevelMap : public DrawableObject
{
public:
	LevelMap();
	LevelMap(std::string filename);
	LevelMap(const LevelMap& lm) = delete;
	LevelMap& operator=(const LevelMap& lm) = delete;
	virtual ~LevelMap();

	virtual void Draw() override;

private:
	std::array<std::array<sf::Sprite*, 16>, 16> map;
};

#endif