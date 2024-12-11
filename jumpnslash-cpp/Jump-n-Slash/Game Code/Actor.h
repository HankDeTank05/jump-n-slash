#ifndef ACTOR_H
#define ACTOR_H

// engine includes
#include "../Engine Code/GameObject.h"
#include "../Engine Code/Sprite.h"

// Forward declarations
class LevelMap;
class RoomData;
class AnimationComponent;

class Actor : public GameObject
{
public:
	Actor() = delete;
	Actor(float speed);
	Actor(const Actor& a) = delete;
	Actor& operator=(const Actor& a) = delete;
	virtual ~Actor();

	virtual void Update(float deltaTime) = 0;

	sf::Vector2f GetConnector(const std::string& name);

protected:
	sf::Vector2f GetPos() const;
	sf::Vector2f GetPosDelta() const;
	float GetWidth() const;
	float GetHeight() const;
	bool IsGrounded() const;
	bool IsHeadBonked() const;
	int GetFacing() const;

	void RaycastRight();
	void RaycastLeft();
	void RaycastUp();
	void RaycastDown();

	void FaceSprite();

protected:
	float speed;
	AnimationComponent* pAnimComp;
	Sprite* pSprite;
	RoomData* pCurrentRoom;
	bool grounded; // Flag to indicate if the actor is grounded
	bool headBonked; // Flag to indicate if the actor is touching a ceiling
	int facing; // 1 for right, -1 for left
};

#endif
