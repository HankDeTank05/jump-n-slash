#include "Scene.h"

#include "RegistrationBroker.h"
#include "DrawManager.h"
#include <cassert>

Scene::Scene()
	: pRegBroker(new RegistrationBroker()),
	pUpdateMgr(new UpdateManager()),
	pDrawMgr(new DrawManager())
{
	// do nothing
}

Scene::~Scene()
{
	delete pDrawMgr;
	delete pUpdateMgr;
	delete pRegBroker;
}

void Scene::Update()
{
	pRegBroker->ExecuteCommands();

	pUpdateMgr->Update();
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

void Scene::AddCommand(Command* pCmd)
{
	pRegBroker->AddCommand(pCmd);
}
