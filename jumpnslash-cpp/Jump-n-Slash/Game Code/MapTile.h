#ifndef MAP_TILE_H
#define MAP_TILE_H

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdatableObject.h"
#include "../Engine Code/DrawableObject.h"

class MapTile : public UpdatableObject, public DrawableObject
{
public:
	MapTile();
	MapTile(const MapTile& mt) = delete;
	MapTile& operator=(const MapTile& mt) = delete;
	virtual ~MapTile();

private:
	sf::Sprite* pSprite;
	sf::Vector2i mapPos;
	bool solidOnTop;
	bool solidOnSides;
	bool solidOnBottom;
};

#endif