#include "SpriteCommandSclChange.h"

// engine includes
#include "Sprite.h"

SpriteCommandSclChange::SpriteCommandSclChange(Sprite* pSprite, sf::Vector2f relative)
	: SpriteCommandScl(pSprite, relative)
{
	// do nothing
}

void SpriteCommandSclChange::Execute()
{
	pSprite->Scale(scl);
}
