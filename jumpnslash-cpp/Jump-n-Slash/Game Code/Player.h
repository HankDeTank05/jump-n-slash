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

#include "Actor.h"

// forward declarations
class PlayerMoveState;
class LevelMap;
class RoomData;

class Player : public Actor, public InputObject, public Subject
{
public:
	Player() = delete;
	Player(LevelMap* pLevel);
	Player(const Player& p) = delete;
	Player& operator=(const Player& p) = delete;
	virtual ~Player();

	// update stuff
	virtual void Update(float deltaTime) override;

	// alarm stuff
	virtual void Alarm0() override;

	// input stuff
	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;
	// collision stuff
	virtual void OnCollisionEnter(CollisionObject* pOther) override;
	virtual void OnCollisionDuring(CollisionObject* pOther) override;
	virtual void OnCollisionExit(CollisionObject* pOther) override;

private: // player accessors. for selective access only (thru attorney)
	friend class PlayerAttorney;
	bool IsApplyGravity();

private: // player mutators. for selective access only (thru attorney)

	// position and movement

	void ProcessInputs(float deltaTime);

	// other

	void SetCurrentRoom(RoomData* pCurrentRoom);

	// animation

	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationJump();
	void SetAnimationFall();

private: // Member variables
	const PlayerMoveState* pCurrentState; // the current movement state
	const PlayerMoveState* pPrevState; // the move state during the previous frame
	sf::Vector2f respawnPoint; // where the player will respawn after dying
	bool walkLeftKeyDown; // flag indicating if the walk left key is currently pressed
	bool walkRightKeyDown; // flag indicating if the walk right key is currently pressed
	bool jumpKeyDown; // flag indicating if the jump jey is currently pressed
	bool applyGravity; // flag indicating if gravity should be applied
};

#endif