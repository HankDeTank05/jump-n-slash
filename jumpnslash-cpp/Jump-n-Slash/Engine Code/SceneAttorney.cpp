#include "SceneAttorney.h"

#include "Scene.h"

void SceneAttorney::GameLoop::Update(Scene* pScene, float deltaTime)
{
	pScene->Update(deltaTime);
}

void SceneAttorney::GameLoop::Draw(Scene* pScene)
{
	pScene->Draw();
}

void SceneAttorney::Commands::AddCommand(Scene* pScene, Command* pCmd)
{
	pScene->AddCommand(pCmd);
}

UpdateManager::UpdateListRef SceneAttorney::Update::Register(Scene* pScene, UpdateObject* pUpdatable)
{
	return pScene->Register(pUpdatable);
}

void SceneAttorney::Update::Deregister(Scene* pScene, UpdateManager::UpdateListRef deleteRef)
{
	pScene->Deregister(deleteRef);
}

DrawManager::DrawListRef SceneAttorney::Draw::Register(Scene* pScene, DrawObject* pDrawable)
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

void SceneAttorney::Input::RegisterMouseCursor(Scene* pScene, InputObject* pInputable)
{
	pScene->RegisterMouseCursor(pInputable);
}

void SceneAttorney::Input::DeregisterMouseCursor(Scene* pScene, InputObject* pInputable)
{
	pScene->DeregisterMouseCursor(pInputable);
}

void SceneAttorney::Input::RegisterGamepadBtn(Scene* pScene, int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToReg)
{
	pScene->RegisterGamepadBtn(gamepadIndex, btnNum, pInputable, eventToReg);
}

void SceneAttorney::Input::DeregisterGamepadBtn(Scene* pScene, int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToDereg)
{
	pScene->DeregisterGamepadBtn(gamepadIndex, btnNum, pInputable, eventToDereg);
}

void SceneAttorney::Input::RegisterGamepadAxis(Scene* pScene, int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToReg)
{
	pScene->RegisterGamepadAxis(gamepadIndex, axis, pInputable, eventToReg);
}

void SceneAttorney::Input::DeregisterGamepadAxis(Scene* pScene, int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToDereg)
{
	pScene->DeregisterGamepadAxis(gamepadIndex, axis, pInputable, eventToDereg);
}

AlarmManager::TimelineRef SceneAttorney::Alarm::Register(Scene* pScene, float triggerTime, AlarmObject* pAlarmable, AlarmID id)
{
	return pScene->Register(triggerTime, pAlarmable, id);
}

void SceneAttorney::Alarm::Deregister(Scene* pScene, AlarmManager::TimelineRef timelineRef)
{
	pScene->Deregister(timelineRef);
}

CollisionManager* SceneAttorney::Collision::GetCollisionManager(Scene* pScene)
{
	return pScene->GetCollisionManager();
}
