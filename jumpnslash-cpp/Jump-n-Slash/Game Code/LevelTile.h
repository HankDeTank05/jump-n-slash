#ifndef LEVEL_TILE_H
#define LEVEL_TILE_H

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"

class LevelTile : public DrawObject
{
public:
	LevelTile() = delete;
	LevelTile(sf::Vector2f pos, sf::Sprite* pSprite, bool solidOnTop, bool solidOnSides, bool solidOnBottom, bool breakable);
	LevelTile(const LevelTile& lt) = delete;
	LevelTile& operator=(const LevelTile& lt) = delete;
	virtual ~LevelTile();

	virtual void Draw() override final;

	bool IsSolidOnTop();
	bool IsSolidOnSides();
	bool IsSolidOnBottom();
	bool IsBreakable();

private:
	sf::Vector2f pos;
	sf::Sprite* pSprite;
	bool solidOnTop;
	bool solidOnSides;
	bool solidOnBottom;
	bool breakable;
};

#endif