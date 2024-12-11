#ifndef SPRITE_COMMAND_SCL_SET_H
#define SPRITE_COMMAND_SCL_SET_H

// engine includes
#include "SpriteCommandScl.h"

class SpriteCommandSclSet : public SpriteCommandScl
{
public:
	SpriteCommandSclSet() = delete;
	SpriteCommandSclSet(Sprite* pSprite, sf::Vector2f scl);
	SpriteCommandSclSet(const SpriteCommandSclSet& scss) = delete;
	SpriteCommandSclSet* operator=(const SpriteCommandSclSet& scss) = delete;
	virtual ~SpriteCommandSclSet() = default;

	virtual void Execute() override;
};

#endif