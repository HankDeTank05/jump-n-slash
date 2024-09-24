#include "SceneAttorney.h"

#include "Scene.h"

void SceneAttorney::GameLoop::Update(Scene* pScene)
{
	pScene->Update();
}

void SceneAttorney::GameLoop::Draw(Scene* pScene)
{
	pScene->Draw();
}

void SceneAttorney::Commands::AddCommand(Scene* pScene, Command* pCmd)
{
	pScene->AddCommand(pCmd);
}

DrawManager::DrawListRef SceneAttorney::Draw::Register(Scene* pScene, DrawableObject* pDrawable)
{
	return pScene->Register(pDrawable);
}
