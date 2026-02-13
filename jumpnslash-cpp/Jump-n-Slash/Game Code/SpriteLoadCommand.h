#ifndef SPRITE_LOAD_COMMAND_H
#define SPRITE_LOAD_COMMAND_H

// game includes
#include "AssetLoadCommand.h"

class SpriteLoadCommand : public AssetLoadCommand
{
public:
	SpriteLoadCommand() = delete;
	SpriteLoadCommand(std::string sprKey, std::string texKey, int x, int y, int w, int h);
	SpriteLoadCommand(const SpriteLoadCommand& slc) = delete;
	SpriteLoadCommand& operator=(const SpriteLoadCommand& slc) = delete;
	virtual ~SpriteLoadCommand() = default;

	virtual void Execute() override;

private:
	std::string sprKey;
	std::string texKey;
	int x;
	int y;
	int w;
	int h;
};

#endif