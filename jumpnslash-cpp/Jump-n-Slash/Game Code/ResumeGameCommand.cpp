#include "ResumeGameCommand.h"

// game includes
#include "GameManager.h"

void ResumeGameCommand::Execute()
{
	GameManager::ResumeFromPause();
}
