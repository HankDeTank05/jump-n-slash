#ifndef SPRITE_COMMAND_POS_CONN_H
#define SPRITE_COMMAND_POS_CONN_H

// language includes
#include <string>

// engine includes
#include "SpriteCommandPos.h"

class SpriteCommandPosConn : public SpriteCommandPos
{
public:
	SpriteCommandPosConn() = delete;
	SpriteCommandPosConn(Sprite* pSprite, std::string connName, sf::Vector2f pos);
	SpriteCommandPosConn(const SpriteCommandPosConn& scpc) = delete;
	SpriteCommandPosConn& operator=(const SpriteCommandPosConn& scpc) = delete;
	virtual ~SpriteCommandPosConn() = default;

	virtual void Execute() override;

private:
	std::string connName;
};

#endif