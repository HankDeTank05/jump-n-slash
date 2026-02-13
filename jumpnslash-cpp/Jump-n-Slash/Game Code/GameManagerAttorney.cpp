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

void GameManagerAttorney::SceneAccess::SetPlayer(Player* pPlayer)
{
	GameManager::SetPlayer(pPlayer);
}

void GameManagerAttorney::SceneAccess::SetLevel(LevelMap* pLevel)
{
	GameManager::SetLevel(pLevel);
}

LevelMap* GameManagerAttorney::PlayerAccess::GetMap()
{
	return GameManager::GetMap();
}

Player* GameManagerAttorney::LevelAccess::GetPlayer()
{
	return GameManager::GetPlayer();
}
