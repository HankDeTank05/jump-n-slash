#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// engine includes
#include "UpdateObject.h"
#include "DrawObject.h"
#include "AlarmObject.h"
#include "CollisionObject.h"
#include "RegistrationState.h"

// forward declarations
class GameObjectRegistrationCommand;
class GameObjectDeregistrationCommand;
class AnimationComponent;

class GameObject : public UpdateObject, public DrawObject, public AlarmObject, public CollisionObject
{
public:
	GameObject();
	GameObject(const GameObject& go) = delete;
	GameObject& operator=(const GameObject& go) = delete;
	virtual ~GameObject();

	void MarkForDestroy();

	virtual void Draw() override final;

protected:
	void RequestSceneEntry();
	void RequestSceneExit();

private:
	friend class GameObjectAttorney;
	virtual void OnSceneEntry();
	virtual void OnSceneExit();
	void EnterScene();
	void ExitScene();

private:
	RegistrationState regState;
	GameObjectRegistrationCommand* pRegCmd;
	GameObjectDeregistrationCommand* pDeregCmd;
	sf::Vector2f pos;
	float width;
	float height;
	Sprite* pSprite;
	AnimationComponent* pAnimComp;
};

#endif