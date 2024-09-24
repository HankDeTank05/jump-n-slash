#include "Scene.h"

#include "RegistrationBroker.h"
#include "DrawManager.h"
#include <cassert>

Scene::Scene()
	: pRegBroker(new RegistrationBroker()),
	pDrawMgr(new DrawManager())
{
	// do nothing
}

Scene::~Scene()
{
	delete pRegBroker;
	delete pDrawMgr;
}

void Scene::Update()
{
	pRegBroker->ExecuteCommands();

	// TODO: unfinished function Scene::Update
}

void Scene::Draw()
{
	pDrawMgr->Draw();
}

DrawManager::DrawListRef Scene::Register(DrawableObject* pDrawable)
{
	return pDrawMgr->Register(pDrawable);
}

void Scene::AddCommand(Command* pCmd)
{
	pRegBroker->AddCommand(pCmd);
}
