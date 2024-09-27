#include "Scene.h"

#include "RegistrationBroker.h"
#include "DrawManager.h"
#include <cassert>

Scene::Scene()
	: pRegBroker(new RegistrationBroker()),
	pUpdateMgr(new UpdateManager()),
	pDrawMgr(new DrawManager()),
	pInputMgr(new InputManager())
{
	// do nothing
}

Scene::~Scene()
{
	delete pInputMgr;
	delete pDrawMgr;
	delete pUpdateMgr;
	delete pRegBroker;
}

void Scene::Update(float deltaTime)
{
	pRegBroker->ExecuteCommands();

	pInputMgr->ProcessKeyboardEvents();
	pInputMgr->ProcessMouseEvents();

	pUpdateMgr->Update(deltaTime);
}

void Scene::Draw()
{
	pDrawMgr->Draw();
}

UpdateManager::UpdateListRef Scene::Register(UpdatableObject* pUpdatable)
{
	return pUpdateMgr->Register(pUpdatable);
}

void Scene::Deregister(UpdateManager::UpdateListRef updateListRef)
{
	pUpdateMgr->Deregister(updateListRef);
}

DrawManager::DrawListRef Scene::Register(DrawableObject* pDrawable)
{
	return pDrawMgr->Register(pDrawable);
}

void Scene::Deregister(DrawManager::DrawListRef drawListRef)
{
	pDrawMgr->Deregister(drawListRef);
}

void Scene::RegisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg)
{
	pInputMgr->RegisterKey(key, pInputable, eventToReg);
}

void Scene::DeregisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg)
{
	pInputMgr->DeregisterKey(key, pInputable, eventToDereg);
}

void Scene::RegisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg)
{
	pInputMgr->RegisterMouseBtn(btn, pInputable, eventToReg);
}

void Scene::DeregisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg)
{
	pInputMgr->DeregisterMouseBtn(btn, pInputable, eventToDereg);
}

void Scene::RegisterMouseCursor(InputObject* pInputable)
{
	pInputMgr->RegisterMouseCursor(pInputable);
}

void Scene::DeregisterMouseCursor(InputObject* pInputable)
{
	pInputMgr->DeregisterMouseCursor(pInputable);
}

void Scene::AddCommand(Command* pCmd)
{
	pRegBroker->AddCommand(pCmd);
}
