#ifndef MAP_TILE_H
#define MAP_TILE_H

// language includes
#include <string>

// library includes
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

// engine includes
#include "../Engine Code/DrawObject.h"

// forward declarations
class Tileset;

class MapTile : public DrawObject
{
public:
	MapTile() = delete;
	MapTile(Tileset* pTileset, std::string skinName);
	MapTile(const MapTile& mt) = delete;
	MapTile& operator=(const MapTile& mt) = delete;
	virtual ~MapTile() = default;

	virtual void Draw() override;

	// mutators

	void SetAppearance(std::string skinName);
	void SetPos(sf::Vector2f newPos);

private:
	Tileset* pTileset;
	Sprite* pSprite;
	sf::Vector2f pos;
};

#endif