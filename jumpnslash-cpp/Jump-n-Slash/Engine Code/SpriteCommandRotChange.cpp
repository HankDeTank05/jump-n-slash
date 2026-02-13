#include "SpriteCommandRotChange.h"

// engine includes
#include "Sprite.h"

SpriteCommandRotChange::SpriteCommandRotChange(Sprite* pSprite, float delta)
	: SpriteCommandRot(pSprite, delta)
{
	// do nothing
}

void SpriteCommandRotChange::Execute()
{
	pSprite->Rotate(rot);
}
