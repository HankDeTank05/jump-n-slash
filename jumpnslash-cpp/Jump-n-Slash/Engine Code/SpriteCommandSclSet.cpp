#include "SpriteCommandSclSet.h"

// engine includes
#include "Sprite.h"

SpriteCommandSclSet::SpriteCommandSclSet(Sprite* pSprite, sf::Vector2f scl)
	: SpriteCommandScl(pSprite, scl)
{
	// do nothing
}

void SpriteCommandSclSet::Execute()
{
	pSprite->SetScale(scl);
}
