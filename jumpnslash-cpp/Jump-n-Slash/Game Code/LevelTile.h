#ifndef LEVEL_TILE_H
#define LEVEL_TILE_H

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdatableObject.h"
#include "../Engine Code/DrawableObject.h"

class LevelTile : public DrawableObject
{
public:
	LevelTile() = delete;
	LevelTile(sf::Vector2f pos, sf::Sprite* pSprite, bool solidOnTop, bool solidOnSides, bool solidOnBottom, bool breakable);
	LevelTile(const LevelTile& lt) = delete;
	LevelTile& operator=(const LevelTile& lt) = delete;
	virtual ~LevelTile();

	virtual void Draw() override final;

private:
	sf::Vector2f pos;
	sf::Sprite* pSprite;
	bool solidOnTop;
	bool solidOnSides;
	bool solidOnBottom;
	bool breakable;
};

#endif