#include "MapTile.h"

// engine includes
#include "../Engine Code/Tileset.h"

MapTile::MapTile(Tileset* _pTileset, std::string _skinName,
	bool _solidOnTop, bool _solidOnSides, bool _solidOnBottom,
	bool _breakable, bool _bouncy,
	float _damageToPlayer, float _damageToEnemies)
	: pTileset(pTileset), pSprite(nullptr), pos(),
	solidOnTop(_solidOnTop), solidOnSides(_solidOnSides), solidOnBottom(_solidOnBottom),
	breakable(_breakable), bouncy(_bouncy),
	damageToPlayer(_damageToPlayer), damageToEnemies(_damageToEnemies)

{
	assert(pTileset != nullptr);
	pSprite = pTileset->GetTile(_skinName);
	assert(pSprite != nullptr);
	assert(damageToPlayer >= 0.f);
	assert(damageToEnemies >= 0.f);
}

void MapTile::Draw()
{
	assert(pSprite != nullptr);
	Render(pSprite);
}

void MapTile::SetAppearance(std::string skinName)
{
	pSprite = pTileset->GetTile(skinName);
}

void MapTile::SetPos(sf::Vector2f newPos)
{
	pos = newPos;
}
