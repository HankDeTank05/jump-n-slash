#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <list>

#include <SFML/Graphics.hpp>

#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/InputObject.h"
#include "../Engine Code/AlarmObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/Subject.h"
#include "../Engine Code/AnimationComponent.h"

// forward declarations
class PlayerMoveState;
class LevelMap;
class RoomData;
class Enemy;

class Player : public UpdateObject,
	public DrawObject,
	public InputObject,
	public AlarmObject,
	public CollisionObject,
	public Subject
{
public:
	Player();
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	virtual ~Player();

	// update stuff
	virtual void Update(float deltaTime) override;
	
	// draw stuff
	virtual void Draw() override;

	// alarm stuff
	virtual void Alarm0() override;

	// input stuff
	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;

	// collision stuff
	virtual void OnCollisionEnter(CollisionObject* pOther) override;
	virtual void OnCollisionDuring(CollisionObject* pOther) override;
	virtual void OnCollisionExit(CollisionObject* pOther) override;

	// other stuff
	void LinkToMap(LevelMap* pLevel);

private: // player accessors. for selective access only (thru attorney)
	friend class PlayerAttorney;
	sf::Vector2f GetPos() const;
	sf::Vector2f GetPosDelta() const;
	LevelMap* GetLevel() const;
	bool IsGrounded() const;

private: // player mutators. for selective access only (thru attorney)

	// map collision

	void RaycastRight(float deltaTime);
	void RaycastLeft(float deltaTime);
	void RaycastUp(float deltaTime);
	void RaycastDown(float deltaTime);

	// position and movement

	void SetPos(sf::Vector2f newPos);
	void ApplyGravity(float deltaTime);
	void ProcessInputs(float deltaTime);

	// other

	void SetCurrentRoom(RoomData* pCurrentRoom);

	// animation

	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationJump();
	void SetAnimationFall();

private: // Member variables
	sf::Vector2f pos; // current world-space position
	sf::Vector2f posDelta; // player movement for the current frame (aka, the change from previous frame)
	float speed; // horizontal movement speed
	AnimationComponent animComp; // animation component
	sf::Sprite* pSprite; // the sprite to be drawn
	const PlayerMoveState* pCurrentState; // the current movement state
	const PlayerMoveState* pPrevState; // the move state during the previous frame
	sf::Vector2f respawnPoint; // where the player will respawn after dying
	LevelMap* pLevel; // pointer to the current level (for map collision)
	RoomData* pCurrentRoom; // the reference to the current room the player is in
	bool walkLeftKeyDown; // flag indicating if the walk left key is currently pressed
	bool walkRightKeyDown; // flag indicating if the walk right key is currently pressed
	bool jumpKeyDown; // flag indicating if the jump jey is currently pressed
	bool isGrounded; // flag indicating if the player is touching the ground
	int facing; // 1 for right, -1 for left
};

#endif