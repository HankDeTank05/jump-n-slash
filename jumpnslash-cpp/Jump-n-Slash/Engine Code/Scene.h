#ifndef SCENE_H
#define SCENE_H

#include "UpdateManager.h"
#include "DrawManager.h"
#include "InputManager.h"
#include "AlarmManager.h"
#include "AlarmID.h"
#include "CollisionManager.h"

// forward declarations
class Command;
class RegistrationBroker;
class UpdateObject;
class DrawObject;
class Camera;
class CameraManager;
class CollisionManager;

class Scene
{
public:
	Scene();
	Scene(const Scene& s) = delete;
	Scene& operator=(const Scene& s) = delete;
	virtual ~Scene();

	// TODO: docs for Scene::Init
	virtual void Init() = 0; 
	// TODO: docs for Scene::End
	virtual void End() = 0; 

	// TODO: docs for Scene::SetCurrentCamera
	void SetCurrentCamera(Camera* pCam);
	// TODO: docs for Scene::GetCurrentCamera
	Camera* GetCurrentCamera();

private:
	friend class SceneAttorney;
	void Update(float deltaTime);
	void Draw();

	// update registration

	UpdateManager::UpdateListRef Register(UpdateObject* pUpdatable);
	void Deregister(UpdateManager::UpdateListRef updateListRef);

	// draw registration

	DrawManager::DrawListRef Register(DrawObject* pDrawable);
	void Deregister(DrawManager::DrawListRef drawListRef);

	// input registration

	void RegisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToReg);
	void DeregisterKey(sf::Keyboard::Key key, InputObject* pInputable, KeyEvent eventToDereg);
	void RegisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToReg);
	void DeregisterMouseBtn(sf::Mouse::Button btn, InputObject* pInputable, MouseEvent eventToDereg);
	void RegisterMouseCursor(InputObject* pInputable);
	void DeregisterMouseCursor(InputObject* pInputable);
	void RegisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToReg);
	void DeregisterGamepadBtn(int gamepadIndex, int btnNum, InputObject* pInputable, GamepadBtnEvent eventToDereg);
	void RegisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToReg);
	void DeregisterGamepadAxis(int gamepadIndex, sf::Joystick::Axis axis, InputObject* pInputable, GamepadAxisEvent eventToDereg);

	// alarm registration

	AlarmManager::TimelineRef Register(float triggerTime, AlarmObject* pAlarmable, AlarmID id);
	void Deregister(AlarmManager::TimelineRef timelineRef);

	// collision registration

	CollisionManager* GetCollisionManager();

	// registration broker

	void AddCommand(Command* pCmd);

protected: // collision functions
	// TODO: docs for Scene::SetCollisionPair
	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		pColMgr->SetCollisionPair<C1, C2>();
	}

	// TODO: docs for Scene::SetCollisionSelf
	template <typename C>
	void SetCollisionSelf()
	{
		pColMgr->SetCollisionSelf<C>();
	}

private:
	RegistrationBroker* pRegBroker; // manages registration with gameobject managers

	UpdateManager* pUpdateMgr; // manages update objects
	DrawManager* pDrawMgr; // manages draw objects
	InputManager* pInputMgr; // manages input objects
	AlarmManager* pAlarmMgr; // manages alarm objects
	CollisionManager* pColMgr; // manages collision objects

	CameraManager* pCamMgr; // manages the camera(s)
};

#endif