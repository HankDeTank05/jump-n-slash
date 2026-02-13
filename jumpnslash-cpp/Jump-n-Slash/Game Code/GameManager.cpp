#include "GameManager.h"

// engine includes
#include "../Engine Code/SceneManager.h"
#include "../Engine Code/EngineAttorney.h"

// game includes
#include "GameFSM.h"
#include "Level0.h"
#include "TestScene.h"
#include "ControlSelection.h"
#include "PauseMenuScene.h"
#include "CompoundSpriteScene.h"

GameManager* GameManager::pInstance = nullptr;

GameManager::GameManager()
	: pCurrentState(nullptr),
	pPlayer(nullptr),
	pLevel(nullptr)
{
	// do nothing
}

GameManager& GameManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new GameManager();
	}
	return *pInstance;
}

void GameManager::StartGame()
{
	Instance().privStartGame();
}

void GameManager::PauseGame()
{
	Instance().privPauseGame();
}

void GameManager::ResumeFromPause()
{
	Instance().privResumeFromPause();
}

void GameManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void GameManager::QuitGame()
{
	Instance().privQuitGame();
}

void GameManager::SetPlayer(Player* pPlayer)
{
	Instance().privSetPlayer(pPlayer);
}

void GameManager::SetLevel(LevelMap* pLevel)
{
	Instance().privSetLevel(pLevel);
}

Player* GameManager::GetPlayer()
{
	return Instance().privGetPlayer();
}

LevelMap* GameManager::GetMap()
{
	return Instance().privGetLevel();
}

void GameManager::privStartGame()
{
	//*
	SceneManager::SetStartScene(new Level0());
	pCurrentState = &GameFSM::playing;
	//*/
	
	/*
	SceneManager::SetStartScene(new ControlSelection());
	pCurrentState = &GameFSM::menu
	//*/
	
	/*
	SceneManager::SetStartScene(new TestScene());
	pCurrentState = &GameFSM::playing;
	//*/
	
	/*
	SceneManager::SetStartScene(new CompoundSpriteScene());
	pCurrentState = &GameFSM::playing;
	//*/
}

void GameManager::privPauseGame()
{
	//SceneManager::SetNextSceneSuspend(new ControlSelection());
	SceneManager::SetNextSceneSuspend(new PauseMenuScene());
	pCurrentState = &GameFSM::menu;
}

void GameManager::privResumeFromPause()
{
	SceneManager::SetNextSceneResume();
	pCurrentState = &GameFSM::playing;
}

void GameManager::privQuitGame()
{
	EngineAttorney::QuitGameAccess::RequestQuitGame();
}

void GameManager::privSetPlayer(Player* _pPlayer)
{
	assert(_pPlayer != nullptr);
	pPlayer = _pPlayer;
}

void GameManager::privSetLevel(LevelMap* _pLevel)
{
	assert(_pLevel != nullptr);
	pLevel = _pLevel;
}

Player* GameManager::privGetPlayer()
{
	return pPlayer;
}

LevelMap* GameManager::privGetLevel()
{
	return pLevel;
}
