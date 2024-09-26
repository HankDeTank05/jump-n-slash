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

UpdateManager::UpdateListRef SceneAttorney::Update::Register(Scene* pScene, UpdatableObject* pUpdatable)
{
	return pScene->Register(pUpdatable);
}

void SceneAttorney::Update::Deregister(Scene* pScene, UpdateManager::UpdateListRef deleteRef)
{
	pScene->Deregister(deleteRef);
}

DrawManager::DrawListRef SceneAttorney::Draw::Register(Scene* pScene, DrawableObject* pDrawable)
{
	return pScene->Register(pDrawable);
}

void SceneAttorney::Draw::Deregister(Scene* pScene, DrawManager::DrawListRef deleteRef)
{
	pScene->Deregister(deleteRef);
}

void SceneAttorney::Input::RegisterKey(Scene* pScene, sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg)
{
	pScene->RegisterKey(key, pInputable, eventToReg);
}

void SceneAttorney::Input::DeregisterKey(Scene* pScene, sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg)
{
	pScene->DeregisterKey(key, pInputable, eventToDereg);
}

void SceneAttorney::Input::RegisterMouseBtn(Scene* pScene, sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg)
{
	pScene->RegisterMouseBtn(btn, pInputable, eventToReg);
}

void SceneAttorney::Input::DeregisterMouseBtn(Scene* pScene, sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg)
{
	pScene->DeregisterMouseBtn(btn, pInputable, eventToDereg);
}
