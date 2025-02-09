#include "TextureLoadCommand.h"

// engine includes
#include "../Engine Code/TextureManager.h"

TextureLoadCommand::TextureLoadCommand(std::string _key, std::string _filename, bool _smooth)
	: key(_key),
	filename(_filename),
	smooth(_smooth)
{
	// do nothing
}

void TextureLoadCommand::Execute()
{
	TextureManager::LoadTexture(key, filename, smooth);
}
