#ifndef SPRITE_COMMAND_SCL_CHANGE_H
#define SPRITE_COMMAND_SCL_CHANGE_H

// engine includes
#include "SpriteCommandScl.h"

class SpriteCommandSclChange : public SpriteCommandScl
{
public:
	SpriteCommandSclChange() = delete;
	SpriteCommandSclChange(Sprite* pSprite, sf::Vector2f relative);
	SpriteCommandSclChange(const SpriteCommandSclChange& scsc) = delete;
	SpriteCommandSclChange& operator=(const SpriteCommandSclChange& scsc) = delete;
	virtual ~SpriteCommandSclChange() = default;

	virtual void Execute() override;
};

#endif