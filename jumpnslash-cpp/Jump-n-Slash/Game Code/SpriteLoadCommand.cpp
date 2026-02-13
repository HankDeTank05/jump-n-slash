#include "SpriteLoadCommand.h"

// engine includes
#include "../Engine Code/SpriteManager.h"

SpriteLoadCommand::SpriteLoadCommand(std::string _sprKey, std::string _texKey, int _x, int _y, int _w, int _h)
	: sprKey(_sprKey),
	texKey(_texKey),
	x(_x), y(_y),
	w(_w), h(_h)
{
	// do nothing
}

void SpriteLoadCommand::Execute()
{
	SpriteManager::LoadSprite(sprKey, texKey, sf::IntRect(x, y, w, h));
}
