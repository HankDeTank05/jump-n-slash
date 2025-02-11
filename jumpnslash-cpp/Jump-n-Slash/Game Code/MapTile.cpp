#include "MapTile.h"

// engine includes
#include "../Engine Code/Tileset.h"

MapTile::MapTile(Tileset* _pTileset, std::string skinName)
	: pTileset(_pTileset),
	pSprite(pTileset->GetTile(skinName)),
	pos()
{
	assert(pTileset != nullptr);
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
