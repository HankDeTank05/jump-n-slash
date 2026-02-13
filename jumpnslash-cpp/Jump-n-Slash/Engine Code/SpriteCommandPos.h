#ifndef SPRITE_COMMAND_POS_BASE_H
#define SPRITE_COMMAND_POS_BASE_H

// library includes
#include <SFML/System/Vector2.hpp>

// engine includes
#include "SpriteCommand.h"

class SpriteCommandPos : public SpriteCommand
{
public:
	SpriteCommandPos() = delete;
	SpriteCommandPos(Sprite* pSprite, sf::Vector2f pos);
	SpriteCommandPos(const SpriteCommandPos& scp) = delete;
	SpriteCommandPos& operator=(const SpriteCommandPos& scp) = delete;
	virtual ~SpriteCommandPos() = default;

	virtual void Execute() = 0;

protected:
	sf::Vector2f pos;
};

#endif