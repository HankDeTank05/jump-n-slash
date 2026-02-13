#include "SpriteCommandPosConn.h"

// engine includes
#include "Sprite.h"

SpriteCommandPosConn::SpriteCommandPosConn(Sprite* pSprite, std::string _connName, sf::Vector2f pos)
	: SpriteCommandPos(pSprite, pos),
	connName(_connName)
{
	// do nothing
}

void SpriteCommandPosConn::Execute()
{
	pSprite->SetPositionByConnector(connName, pos);
}
