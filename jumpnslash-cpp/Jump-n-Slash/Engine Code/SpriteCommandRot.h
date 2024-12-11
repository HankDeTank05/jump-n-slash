#ifndef SPRITE_COMMAND_ROT_H
#define SPRITE_COMMAND_ROT_H

// engine includes
#include "SpriteCommand.h"

class SpriteCommandRot : public SpriteCommand
{
public:
	SpriteCommandRot() = delete;
	SpriteCommandRot(Sprite* pSprite, float rot);
	SpriteCommandRot(const SpriteCommandRot& scr) = delete;
	SpriteCommandRot& operator=(const SpriteCommandRot& scr) = delete;
	virtual ~SpriteCommandRot() = default;

	virtual void Execute() = 0;

protected:
	float rot;
};

#endif