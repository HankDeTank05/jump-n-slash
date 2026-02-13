#ifndef ENGINE_QUIT_COMMAND_BASE_H
#define ENGINE_QUIT_COMMAND_BASE_H

// engine includes
#include "Command.h"

class EngineQuitCommandBase : public Command
{
public:
	EngineQuitCommandBase() = default;
	EngineQuitCommandBase(const EngineQuitCommandBase& eqcb) = delete;
	EngineQuitCommandBase& operator=(const EngineQuitCommandBase& eqcb) = delete;
	virtual ~EngineQuitCommandBase() = default;

	virtual void Execute() = 0;
};

#endif