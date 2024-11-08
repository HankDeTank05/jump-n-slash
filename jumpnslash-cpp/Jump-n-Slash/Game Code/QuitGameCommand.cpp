#include "QuitGameCommand.h"

// game includes
#include "GameManagerAttorney.h"

void QuitGameCommand::Execute()
{
	GameManagerAttorney::QuitGameAccess::QuitGame();
}
