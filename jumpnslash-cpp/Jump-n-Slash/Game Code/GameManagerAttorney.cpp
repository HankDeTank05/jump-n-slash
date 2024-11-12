#include "GameManagerAttorney.h"

// game includes
#include "GameManager.h"

void GameManagerAttorney::EngineAccess::Terminate()
{
	GameManager::Terminate();
}

void GameManagerAttorney::QuitGameAccess::QuitGame()
{
	GameManager::QuitGame();
}
