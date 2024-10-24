#include "Scene.h"

#include <cassert>

#include "RegistrationBroker.h"
#include "DrawManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"

Scene::Scene()
	: pRegBroker(new RegistrationBroker()),
	pUpdateMgr(new UpdateManager()),
	pDrawMgr(new DrawManager()),
	pInputMgr(new InputManager()),
	pAlarmMgr(new AlarmManager()),
	pColMgr(new CollisionManager()),
	pCamMgr(new CameraManager())
{
	// do nothing
}

Scene::~Scene()
{
	delete pCamMgr;
	delete pColMgr;
	delete pAlarmMgr;
	delete pInputMgr;
	delete pDrawMgr;
	delete pUpdateMgr;
	delete pRegBroker;
}

void Scene::SetCurrentCamera(Camera* pCam)
{
	pCamMgr->SetCurrentCamera(pCam);
}

Camera* Scene::GetCurrentCamera()
{
	return pCamMgr->GetCurrentCamera();
}

void Scene::Update(float deltaTime)
{
	pRegBroker->ExecuteCommands();

	pAlarmMgr->ProcessAlarms(); // TODO: make sure this actually works

	pInputMgr->ProcessKeyboardEvents();
	pInputMgr->ProcessMouseEvents();

	pUpdateMgr->Update(deltaTime);

	pColMgr->ComputeData();
	pColMgr->ProcessCollisions();
}

void Scene::Draw()
{
	pDrawMgr->Draw();
}

UpdateManager::UpdateListRef Scene::Register(UpdateObject* pUpdatable)
{
	return pUpdateMgr->Register(pUpdatable);
}

void Scene::Deregister(UpdateManager::UpdateListRef updateListRef)
{
	pUpdateMgr->Deregister(updateListRef);
}

DrawManager::DrawListRef Scene::Register(DrawObject* pDrawable)
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

AlarmManager::TimelineRef Scene::Register(float triggerTime, AlarmObject* pAlarmable, AlarmID id)
{
	return pAlarmMgr->Register(triggerTime, pAlarmable, id);
}

void Scene::Deregister(AlarmManager::TimelineRef timelineRef)
{
	pAlarmMgr->Deregister(timelineRef);
}

CollisionManager* Scene::GetCollisionManager()
{
	return pColMgr;
}

void Scene::AddCommand(Command* pCmd)
{
	pRegBroker->AddCommand(pCmd);
}
