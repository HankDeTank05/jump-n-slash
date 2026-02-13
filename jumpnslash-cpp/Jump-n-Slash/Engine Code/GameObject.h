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

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() override;

protected:
	sf::Vector2f GetPos() const;
	sf::Vector2f GetPosDelta() const;
	float GetWidth() const;
	float GetHeight() const;

	void UpdateSprite();
	void SetWidth();
	void SetHeight();
	void SetPosition(const sf::Vector2f& newPos);

	void RequestSceneEntry();
	void RequestSceneExit();

private:
	friend class GameObjectAttorney;
	virtual void OnSceneEntry();
	virtual void OnSceneExit();
	void EnterScene();
	void ExitScene();

private: // engine-only member variables
	RegistrationState regState;
	GameObjectRegistrationCommand* pRegCmd;
	GameObjectDeregistrationCommand* pDeregCmd;
protected: // member variables
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	float width;
	float height;
	Sprite* pSprite;
	AnimationComponent* pAnimComp;
};

#endif