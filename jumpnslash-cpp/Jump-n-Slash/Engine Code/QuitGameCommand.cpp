#include "QuitGameCommand.h"

// engine includes
#include "EngineAttorney.h"

void QuitGameCommand::Execute()
{
	EngineAttorney::QuitGameAccess::RequestQuitGame();
}
