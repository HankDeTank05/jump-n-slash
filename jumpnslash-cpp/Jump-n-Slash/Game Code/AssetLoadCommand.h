#ifndef ASSET_LOAD_COMMAND_H
#define ASSET_LOAD_COMMAND_H

// engine includes
#include "../Engine Code/Command.h"

class AssetLoadCommand : public Command
{
public:
	AssetLoadCommand() = default;
	AssetLoadCommand(const AssetLoadCommand& alc) = delete;
	AssetLoadCommand& operator=(const AssetLoadCommand& alc) = delete;
	virtual ~AssetLoadCommand() = default;

	virtual void Execute() = 0;
};

#endif