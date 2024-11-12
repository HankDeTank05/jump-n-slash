#include "../Engine Code/JumpSlashEngine.h"

// game includes
#include "ControllerDebuggerAttorney.h"
#include "GameManagerAttorney.h"

void JumpSlashEngine::GameEnd()
{
	ControllerDebuggerAttorney::EngineAccess::Terminate();
	GameManagerAttorney::EngineAccess::Terminate();
}