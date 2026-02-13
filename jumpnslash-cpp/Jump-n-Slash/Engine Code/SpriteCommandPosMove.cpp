#include "SpriteCommandPosMove.h"

// engine includes
#include "Sprite.h"

SpriteCommandPosMove::SpriteCommandPosMove(Sprite* pSprite, sf::Vector2f delta)
	: SpriteCommandPos(pSprite, delta)
{
	// do nothing
}

void SpriteCommandPosMove::Execute()
{
	pSprite->Move(pos);
}
