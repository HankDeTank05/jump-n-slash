#include "SpriteCommandScl.h"

SpriteCommandScl::SpriteCommandScl(Sprite* pSprite, sf::Vector2f _scl)
	: SpriteCommand(pSprite),
	scl(_scl)
{
	// do nothing
}
