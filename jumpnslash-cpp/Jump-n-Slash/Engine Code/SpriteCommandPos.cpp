#include "SpriteCommandPos.h"

SpriteCommandPos::SpriteCommandPos(Sprite* pSprite, sf::Vector2f _pos)
	: SpriteCommand(pSprite),
	pos(_pos)
{
	// do nothing
}
