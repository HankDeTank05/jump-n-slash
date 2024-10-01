#include "BlockSolid.h"

#include "../Engine Code/SpriteManager.h"

BlockSolid::BlockSolid(sf::Vector2f pos)
	: LevelTile(pos, SpriteManager::GetSprite("block solid"), true, true, true, false)
{
	// Do nothing
}

BlockSolid::~BlockSolid()
{
	// Do nothing
}
