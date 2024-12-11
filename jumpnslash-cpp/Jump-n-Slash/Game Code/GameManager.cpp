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
	: pCurrentState(nullptr)
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
