#include "BlockHazard.h"

#include "../Engine Code/SpriteManager.h"

#include "Constants.h"

BlockHazard::BlockHazard(sf::Vector2f pos)
	: LevelTile(pos, SpriteManager::GetSprite(KEY_BLOCK_HAZARD), true, true, true, false)
{
	RequestDrawRegistration();
}

BlockHazard::~BlockHazard()
{
	// do nothing
}
