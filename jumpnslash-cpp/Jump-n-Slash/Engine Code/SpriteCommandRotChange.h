#ifndef SPRITE_COMMAND_ROT_CHANGE_H
#define SPRIET_COMMAND_ROT_CHANGE_H

// engine includes
#include "SpriteCommandRot.h"

class SpriteCommandRotChange : public SpriteCommandRot
{
public:
	SpriteCommandRotChange() = delete;
	SpriteCommandRotChange(Sprite* pSprite, float delta);
	SpriteCommandRotChange(const SpriteCommandRotChange& scrc) = delete;
	SpriteCommandRotChange& operator=(const SpriteCommandRotChange& scrc) = delete;
	virtual ~SpriteCommandRotChange() = default;

	virtual void Execute() override;
};

#endif