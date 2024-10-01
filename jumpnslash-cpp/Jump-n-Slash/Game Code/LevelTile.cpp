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
	// do nothing
}

LevelTile::~LevelTile()
{
	// do nothing
}

void LevelTile::Draw()
{
	pSprite->setPosition(pos);
	JumpSlashEngine::GetWindow().draw(*pSprite);
}
