#include "SpriteCommandPosSet.h"

// engine includes
#include "Sprite.h"

SpriteCommandPosSet::SpriteCommandPosSet(Sprite* pSprite, sf::Vector2f pos)
	: SpriteCommandPos(pSprite, pos)
{
	// do nothing
}

void SpriteCommandPosSet::Execute()
{
	pSprite->SetPosition(pos);
}
