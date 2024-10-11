#include "SceneManager.h"

#include "Scene.h"
#include "SceneCommand.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include "SceneAttorney.h"

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
	: pCurrentScene(nullptr),
	pChangeCmd(new SceneChangeCommand()),
	pDontChangeCmd(new SceneChangeNullCommand()),
	pCmdToExe(pDontChangeCmd)
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

void SceneManager::SetNextScene(Scene* pNextScene)
{
	Instance().privSetNextScene(pNextScene);
}

void SceneManager::InitStartScene()
{
	Instance().privInitStartScene();
}

void SceneManager::ChangeScene(Scene* pScene)
{
	Instance().privChangeScene(pScene);
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

void SceneManager::privSetNextScene(Scene* pNextScene)
{
	assert(pCmdToExe != pChangeCmd);
	assert(pNextScene != pCurrentScene); // tom foolery such as this is strictly prohibited

	pChangeCmd->SetNextScene(pNextScene);
	pCmdToExe = pChangeCmd;
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

void SceneManager::privUpdateCurrentScene(float deltaTime)
{
	pCmdToExe->Execute();

	SceneAttorney::GameLoop::Update(pCurrentScene, deltaTime);
}

void SceneManager::privDrawCurrentScene()
{
	SceneAttorney::GameLoop::Draw(pCurrentScene);
}
