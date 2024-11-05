#include "../Engine Code/JumpSlashEngine.h"

#include "../Engine Code/ControlManagerAttorney.h"

#include "ControllerDebuggerAttorney.h"

void JumpSlashEngine::GameEnd()
{
	ControlManagerAttorney::EngineAccess::Terminate();
	ControllerDebuggerAttorney::EngineAccess::Terminate();
}