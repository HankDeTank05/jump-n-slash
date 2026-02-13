#ifndef TEXTURE_LOAD_COMMAND_H
#define TEXTURE_LOAD_COMMAND_H

// game includes
#include "AssetLoadCommand.h"

class TextureLoadCommand : public AssetLoadCommand
{
public:
	TextureLoadCommand() = delete;
	TextureLoadCommand(std::string key, std::string filename, bool smooth);
	TextureLoadCommand(const TextureLoadCommand& tlc) = delete;
	TextureLoadCommand& operator=(const TextureLoadCommand& tlc) = delete;
	virtual ~TextureLoadCommand() = default;

	virtual void Execute() override;

private:
	std::string key;
	std::string filename;
	bool smooth;
};

#endif