#ifndef MAP_TILE_H
#define MAP_TILE_H

#include <SFML/Graphics.hpp>

class MapTile
{
public:
	MapTile();
	MapTile(const MapTile& mt) = delete;
	MapTile& operator=(const MapTile& mt) = delete;
	virtual ~MapTile();

private:
	sf::Sprite* pSprite;
	bool solidOnTop;
	bool solidOnSide;
	bool solidOnBottom;
	bool breakable;
};

#endif