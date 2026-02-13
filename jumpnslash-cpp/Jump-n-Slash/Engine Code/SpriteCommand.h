#ifndef SPRITE_COMMAND_H
#define SPRITE_COMMAND_H

// engine includes
#include "Command.h"

// forward declarations
class Sprite;

class SpriteCommand : public Command
{
public:
	SpriteCommand() = delete;
	SpriteCommand(Sprite* pSprite);
	SpriteCommand(const SpriteCommand& sc) = delete;
	SpriteCommand& operator=(const SpriteCommand& sc) = delete;
	virtual ~SpriteCommand() = default;

	virtual void Execute() = 0;

protected:
	Sprite* pSprite;
};

#endif