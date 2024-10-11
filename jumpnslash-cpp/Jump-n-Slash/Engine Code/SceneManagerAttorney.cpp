#include "SceneManagerAttorney.h"

#include "SceneManager.h"

void SceneManagerAttorney::Initialization::InitStartScene()
{
	SceneManager::InitStartScene();
}

void SceneManagerAttorney::GameLoop::UpdateCurrentScene(float deltaTime)
{
	SceneManager::UpdateCurrentScene(deltaTime);
}

void SceneManagerAttorney::GameLoop::DrawCurrentScene()
{
	SceneManager::DrawCurrentScene();
}

void SceneManagerAttorney::SceneChange::ChangeScene(Scene* pScene)
{
	SceneManager::ChangeScene(pScene);
}

void SceneManagerAttorney::Termination::Terminate()
{
	SceneManager::Terminate();
}
