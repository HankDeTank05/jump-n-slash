#ifndef SPRITE_COMMAND_POS_SET_H
#define SPRITE_COMMAND_POS_SET_H

// engine includes
#include "SpriteCommandPos.h"

class SpriteCommandPosSet : public SpriteCommandPos
{
public:
	SpriteCommandPosSet() = delete;
	SpriteCommandPosSet(Sprite* pSprite, sf::Vector2f pos);
	SpriteCommandPosSet(const SpriteCommandPosSet& scps) = delete;
	SpriteCommandPosSet& operator=(const SpriteCommandPosSet& scps) = delete;
	virtual ~SpriteCommandPosSet() = default;

	virtual void Execute() override;
};

#endif