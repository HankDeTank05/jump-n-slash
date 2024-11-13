#ifndef ENGINE_QUIT_COMMAND_H
#define ENGINE_QUIT_COMMAND_H

// engine includes
#include "EngineQuitCommandBase.h"

class EngineQuitCommand : public EngineQuitCommandBase
{
public:
	EngineQuitCommand() = default;
	EngineQuitCommand(const EngineQuitCommand& eqc) = delete;
	EngineQuitCommand& operator=(const EngineQuitCommand& eqc) = delete;
	virtual ~EngineQuitCommand() = default;
	
	virtual void Execute() override;
};

#endif