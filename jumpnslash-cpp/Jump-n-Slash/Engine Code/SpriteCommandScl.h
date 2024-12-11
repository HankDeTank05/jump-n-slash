#ifndef SPRITE_COMMAND_SCL_H
#define SPRITE_COMMAND_SCL_H

// library includes
#include <SFML/System/Vector2.hpp>

// engine includes
#include "SpriteCommand.h"

class SpriteCommandScl : public SpriteCommand
{
public:
	SpriteCommandScl() = delete;
	SpriteCommandScl(Sprite* pSprite, sf::Vector2f scl);
	SpriteCommandScl(const SpriteCommandScl& scs) = delete;
	SpriteCommandScl& operator=(const SpriteCommandScl scs) = delete;
	virtual ~SpriteCommandScl() = default;

	virtual void Execute() = 0;

protected:
	sf::Vector2f scl;
};

#endif