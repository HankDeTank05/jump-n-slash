#include "SpriteCommandRot.h"

SpriteCommandRot::SpriteCommandRot(Sprite* pSprite, float _rot)
	: SpriteCommand(pSprite),
	rot(_rot)
{
	// do nothing
}
