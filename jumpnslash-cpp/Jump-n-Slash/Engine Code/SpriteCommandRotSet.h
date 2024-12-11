#ifndef SPRITE_COMMAND_ROT_SET_H
#define SPRITE_COMMAND_ROT_SET_H

// engine includes
#include "SpriteCommandRot.h"

class SpriteCommandRotSet : public SpriteCommandRot
{
public:
	SpriteCommandRotSet() = delete;
	SpriteCommandRotSet(Sprite* pSprite, float rot);
	SpriteCommandRotSet(const SpriteCommandRotSet& scrs) = delete;
	SpriteCommandRotSet& operator=(const SpriteCommandRotSet& scrs) = delete;
	virtual ~SpriteCommandRotSet() = default;

	virtual void Execute() override;
};

#endif