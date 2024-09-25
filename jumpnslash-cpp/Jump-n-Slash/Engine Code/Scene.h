#ifndef SCENE_H
#define SCENE_H

#include "UpdateManager.h"
#include "DrawManager.h"

// forward declarations
class Command;
class RegistrationBroker;
class UpdatableObject;
class DrawableObject;

class Scene
{
public:
	Scene();
	Scene(const Scene& s) = delete;
	Scene& operator=(const Scene& s) = delete;
	virtual ~Scene();

	virtual void Init() = 0; // TODO: documentation for Scene::Init
	virtual void End() = 0; // TODO: documentation for Scene::End

private:
	friend class SceneAttorney;
	void Update();
	void Draw();

	UpdateManager::UpdateListRef Register(UpdatableObject* pUpdatable);
	void Deregister(UpdateManager::UpdateListRef updateListRef);

	DrawManager::DrawListRef Register(DrawableObject* pDrawable);
	void Deregister(DrawManager::DrawListRef drawListRef);

	void AddCommand(Command* pCmd);

private:
	RegistrationBroker* pRegBroker;

	UpdateManager* pUpdateMgr;
	DrawManager* pDrawMgr;
};

#endif