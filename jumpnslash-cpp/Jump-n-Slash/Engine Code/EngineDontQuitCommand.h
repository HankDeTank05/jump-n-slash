#ifndef ENGINE_DONT_QUIT_COMMAND_H
#define ENGINE_DONT_QUIT_COMMAND_h

// engine includes
#include "EngineQuitCommandBase.h"

class EngineDontQuitCommand : public EngineQuitCommandBase
{
public:
	EngineDontQuitCommand() = default;
	EngineDontQuitCommand(const EngineDontQuitCommand& edqc) = delete;
	EngineDontQuitCommand& operator=(const EngineDontQuitCommand& edqc) = delete;
	virtual ~EngineDontQuitCommand() = default;

	virtual void Execute() override;
};

#endif