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
#include "ControlScheme.h"

// forward declarations
class PlayerMoveState;
class PlayerControlStrategy;
class LevelMap;
class RoomData;

class Player : public Actor, public InputObject, public Subject
{
public:
	Player() = delete;
	Player(LevelMap* pLevel, ControlScheme scheme);
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
	void SetWalk(float direction);
	void SetJump(bool enabled);

	// other

	void SetCurrentRoom(RoomData* pCurrentRoom);

	// animation

	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationJump();
	void SetAnimationFall();

private: // Member variables
	PlayerControlStrategy* pCtrlStrat;
	const PlayerMoveState* pCurrentState; // the current movement state
	const PlayerMoveState* pPrevState; // the move state during the previous frame
	sf::Vector2f respawnPoint; // where the player will respawn after dying
	//bool inputReceivedWalkLeft; // flag indicating if the walk left input is currently being received
	//bool inputReceivedWalkRight; // flag indicating if the walk right input is currently being received
	float inputWalkDir; // float in range [-1, 1] indicating which direction to walk and how fast
	bool inputReceivedJump; // flag indicating if the jump input is currently being received
	bool applyGravity; // flag indicating if gravity should be applied
};

#endif