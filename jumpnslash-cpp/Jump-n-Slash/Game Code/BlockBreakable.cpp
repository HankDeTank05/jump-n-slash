#include "BlockBreakable.h"

#include "../Engine Code/SpriteManager.h"

#include "Constants.h"

BlockBreakable::BlockBreakable(sf::Vector2f pos)
	: LevelTile(pos, SpriteManager::GetSprite(KEY_BLOCK_BREAKABLE), true, true, true, true)
{
	EnqueueForDrawRegistration();
}

BlockBreakable::~BlockBreakable()
{
	// do nothing
}

void BlockBreakable::Update()
{
	// do nothing
}

void BlockBreakable::Break()
{
	EnqueueForDrawDeregistration();
}
