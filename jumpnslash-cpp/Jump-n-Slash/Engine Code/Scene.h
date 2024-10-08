#ifndef SCENE_H
#define SCENE_H

#include "UpdateManager.h"
#include "DrawManager.h"
#include "InputManager.h"

// forward declarations
class Command;
class RegistrationBroker;
class UpdateObject;
class DrawObject;

class Scene
{
public:
	Scene();
	Scene(const Scene& s) = delete;
	Scene& operator=(const Scene& s) = delete;
	virtual ~Scene();

	virtual void Init() = 0; // TODO: docs for Scene::Init
	virtual void End() = 0; // TODO: docs for Scene::End

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

	// registration broker
	void AddCommand(Command* pCmd);

private:
	RegistrationBroker* pRegBroker;

	UpdateManager* pUpdateMgr;
	DrawManager* pDrawMgr;
	InputManager* pInputMgr;
};

#endif