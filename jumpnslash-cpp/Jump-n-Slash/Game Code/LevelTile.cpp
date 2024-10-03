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

bool LevelTile::IsSolidOnTop()
{
	return solidOnTop;
}

bool LevelTile::IsSolidOnSides()
{
	return solidOnSides;
}

bool LevelTile::IsSolidOnBottom()
{
	return solidOnBottom;
}

bool LevelTile::IsBreakable()
{
	return breakable;
}
