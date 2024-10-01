#include "PlatformSemisolid.h"

#include "../Engine Code/SpriteManager.h"

PlatformSemisolid::PlatformSemisolid(sf::Vector2f pos)
	: LevelTile(pos, SpriteManager::GetSprite(""), true, false, false, false) // No key for the sprite
{
	// Do nothing
}

PlatformSemisolid::~PlatformSemisolid()
{
	// Do nothing
}
