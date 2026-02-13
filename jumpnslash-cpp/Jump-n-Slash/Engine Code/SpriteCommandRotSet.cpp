#include "SpriteCommandRotSet.h"

// engine includes
#include "Sprite.h"

SpriteCommandRotSet::SpriteCommandRotSet(Sprite* pSprite, float rot)
	: SpriteCommandRot(pSprite, rot)
{
	// do nothing
}

void SpriteCommandRotSet::Execute()
{
	pSprite->SetRotation(rot);
}
