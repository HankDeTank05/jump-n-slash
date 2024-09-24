#ifndef SCENE_H
#define SCENE_H

#include "DrawManager.h"

// forward declarations
class Command;
class RegistrationBroker;
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

	// update reg function goes here
	// update dereg function goes here

	DrawManager::DrawListRef Register(DrawableObject* pDrawable);
	void Deregister(DrawManager::DrawListRef drawListRef);

	void AddCommand(Command* pCmd);

private:
	RegistrationBroker* pRegBroker;

	DrawManager* pDrawMgr;
};

#endif