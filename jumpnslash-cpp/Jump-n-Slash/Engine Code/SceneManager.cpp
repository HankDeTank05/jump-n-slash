#include "SceneManager.h"

#include "Scene.h"
#include "SceneCommand.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include "SceneSuspendCommand.h"
#include "SceneResumeCommand.h"
#include "SceneAttorney.h"

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
	: pCurrentScene(nullptr),
	pChangeCmd(new SceneChangeCommand()),
	pDontChangeCmd(new SceneChangeNullCommand()),
	pSuspendCmd(new SceneSuspendCommand()),
	pResumeCmd(new SceneResumeCommand()),
	pCmdToExe(pDontChangeCmd),
	suspensionStack()
{
	// do nothing
}

SceneManager::~SceneManager()
{
	pCurrentScene->End();
	delete pCurrentScene;
	delete pChangeCmd;
	delete pDontChangeCmd;
}

SceneManager& SceneManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new SceneManager();
	}
	return *pInstance;
}

void SceneManager::SetStartScene(Scene* pStartScene)
{
	Instance().privSetStartScene(pStartScene);
}

Scene* SceneManager::GetCurrentScene()
{
	return Instance().privGetCurrentScene();
}

Camera* SceneManager::GetCurrentCamera()
{
	return Instance().privGetCurrentCamera();
}

void SceneManager::SetNextSceneChange(Scene* pNextScene)
{
	Instance().privSetNextSceneChange(pNextScene);
}

void SceneManager::SetNextSceneSuspend(Scene* pNextScene)
{
	Instance().privSetNextSceneSuspend(pNextScene);
}

void SceneManager::SetNextSceneResume()
{
	Instance().privSetNextSceneResume();
}

void SceneManager::InitStartScene()
{
	Instance().privInitStartScene();
}

void SceneManager::ChangeScene(Scene* pScene)
{
	Instance().privChangeScene(pScene);
}

void SceneManager::SuspendCurrentScene(Scene* pForegroundScene)
{
	Instance().privSuspendCurrentScene(pForegroundScene);
}

void SceneManager::ResumeSuspendedScene()
{
	Instance().privResumeSuspendedScene();
}

void SceneManager::UpdateCurrentScene(float deltaTime)
{
	Instance().privUpdateCurrentScene(deltaTime);
}

void SceneManager::DrawCurrentScene()
{
	Instance().privDrawCurrentScene();
}

void SceneManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void SceneManager::privSetStartScene(Scene* pStartScene)
{
	pCurrentScene = pStartScene;
}

Scene* SceneManager::privGetCurrentScene()
{
	return pCurrentScene;
}

Camera* SceneManager::privGetCurrentCamera()
{
	return pCurrentScene->GetCurrentCamera();
}

void SceneManager::privSetNextSceneChange(Scene* pNextScene)
{
	assert(pCmdToExe != pChangeCmd);
	assert(pNextScene != pCurrentScene); // tom foolery such as this is strictly prohibited

	pChangeCmd->SetNextScene(pNextScene);
	pCmdToExe = pChangeCmd;
}

void SceneManager::privSetNextSceneSuspend(Scene* pNextScene)
{
	assert(pCmdToExe != pSuspendCmd);
	assert(pNextScene != pCurrentScene); // tom foolery such as this is strictly prohibited

	pSuspendCmd->SetNextScene(pNextScene);
	pCmdToExe = pSuspendCmd;
}

void SceneManager::privSetNextSceneResume()
{
	assert(suspensionStack.size() > 0);
	
	pCmdToExe = pResumeCmd;
}

void SceneManager::privInitStartScene()
{
	pCurrentScene->Init();
}

void SceneManager::privChangeScene(Scene* pScene)
{
	pCurrentScene->End();

	delete pCurrentScene;

	pCurrentScene = pScene;
	pCurrentScene->Init();

	pCmdToExe = pDontChangeCmd;
}

void SceneManager::privSuspendCurrentScene(Scene* pForegroundScene)
{
	//pCurrentScene->Suspend();

	suspensionStack.push(pCurrentScene);

	pCurrentScene = pForegroundScene;
	pCurrentScene->Init();

	pCmdToExe = pDontChangeCmd;
}

void SceneManager::privResumeSuspendedScene()
{
	assert(suspensionStack.size() > 0);

	pCurrentScene->End();

	delete pCurrentScene;

	pCurrentScene = suspensionStack.top();
	suspensionStack.pop();
	//pCurrentScene->Resume();

	pCmdToExe = pDontChangeCmd;
}

void SceneManager::privUpdateCurrentScene(float deltaTime)
{
	pCmdToExe->Execute();

	SceneAttorney::GameLoop::Update(pCurrentScene, deltaTime);
}

void SceneManager::privDrawCurrentScene()
{
	// draw the most recently suspended scene first (if applicable)
	SceneAttorney::GameLoop::Draw(suspensionStack.top());

	// then draw the current scene on top of it
	SceneAttorney::GameLoop::Draw(pCurrentScene);
}
