#include "EngineQuitCommand.h"

// engine includes
#include "EngineAttorney.h"

void EngineQuitCommand::Execute()
{
	EngineAttorney::CommandAccess::QuitGame();
}
