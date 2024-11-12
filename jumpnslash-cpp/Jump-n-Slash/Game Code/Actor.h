#ifndef ACTOR_H
#define ACTOR_H

#include "../Engine Code/AlarmObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/UpdateObject.h"

// Forward declarations
class LevelMap;
class RoomData;
class AnimationComponent;

class Actor : public AlarmObject, public CollisionObject, public DrawObject, public UpdateObject
{
public:
	Actor() = delete;
	Actor(float speed, LevelMap* pLevel);
	Actor(const Actor& a) = delete;
	Actor& operator=(const Actor& a) = delete;
	virtual ~Actor();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() override final;

protected:
	sf::Vector2f GetPos() const;
	sf::Vector2f GetPosDelta() const;
	LevelMap* GetLevel() const;
	float GetWidth() const;
	float GetHeight() const;
	bool IsGrounded() const;
	bool IsHeadBonked() const;
	float GetFacing() const;

	void RaycastRight();
	void RaycastLeft();
	void RaycastUp();
	void RaycastDown();

	void SetPosition(const sf::Vector2f& newPos);
	void ApplyGravity(float deltaTime);
	void SetWidth();
	void SetHeight();

protected:
	sf::Vector2f pos;
	sf::Vector2f posDelta;
	float width;
	float height;
	float speed;
	AnimationComponent* pAnimComp;
	sf::Sprite* pSprite;
	LevelMap* pLevel;
	RoomData* pCurrentRoom;
	bool grounded; // Flag to indicate if the actor is grounded
	bool headBonked; // Flag to indicate if the actor is touching a ceiling
	int facing; // 1 for right, -1 for left
};

#endif
