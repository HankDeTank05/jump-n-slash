#ifndef LEVEL_TILE_H
#define LEVEL_TILE_H

// library includes
#include <SFML/System/Vector2.hpp>

// engine includes
#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/Tileset.h"

class LevelTile : public DrawObject
{
public:
	LevelTile() = delete;
	LevelTile(sf::Vector2f pos, Tileset* pTileset);
	LevelTile(const LevelTile& lt) = delete;
	LevelTile& operator=(const LevelTile& lt) = delete;
	virtual ~LevelTile();

	virtual void Draw() override final;

	// accessors

	bool IsSolidOnTop() const;
	bool IsSolidOnSides() const;
	bool IsSolidOnBottom() const;
	bool IsBreakable() const;

	sf::Vector2f GetPos() const;

private:
	sf::Vector2f pos;
	Tileset* pTileset;
	Sprite* pSprite;
	bool solidOnTop;
	bool solidOnSides;
	bool solidOnBottom;
	bool breakable;
};

#endif