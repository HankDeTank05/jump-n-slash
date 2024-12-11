#ifndef SPRITE_COMMAND_POS_MOVE_H
#define SPRITE_COMMAND_POS_MOVE_H

// engine includes
#include "SpriteCommandPos.h"

class SpriteCommandPosMove : public SpriteCommandPos
{
public:
	SpriteCommandPosMove() = delete;
	SpriteCommandPosMove(Sprite* pSprite, sf::Vector2f delta);
	SpriteCommandPosMove(const SpriteCommandPosMove& scpm) = delete;
	SpriteCommandPosMove& operator=(const SpriteCommandPosMove& scpm) = delete;
	virtual ~SpriteCommandPosMove() = default;

	virtual void Execute() override;
};

#endif