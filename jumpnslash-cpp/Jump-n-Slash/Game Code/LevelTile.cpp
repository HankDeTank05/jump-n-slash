#include "LevelTile.h"

#include "../Engine Code/JumpSlashEngine.h"

LevelTile::LevelTile(sf::Vector2f _pos, sf::Sprite* _pSprite, bool _solidOnTop, bool _solidOnSides, bool _solidOnBottom, bool _breakable)
	: pos(_pos),
	pSprite(_pSprite),
	solidOnTop(_solidOnTop),
	solidOnSides(_solidOnSides),
	solidOnBottom(_solidOnBottom),
	breakable(_breakable)
{
	RequestDrawRegistration();
}

LevelTile::~LevelTile()
{
	// do nothing
}

void LevelTile::Draw()
{
	pSprite->setPosition(pos);
	Render(*pSprite);
}

bool LevelTile::IsSolidOnTop() const
{
	return solidOnTop;
}

bool LevelTile::IsSolidOnSides() const
{
	return solidOnSides;
}

bool LevelTile::IsSolidOnBottom() const
{
	return solidOnBottom;
}

bool LevelTile::IsBreakable() const
{
	return breakable;
}

sf::Vector2f LevelTile::GetPos() const
{
	return pos;
}
