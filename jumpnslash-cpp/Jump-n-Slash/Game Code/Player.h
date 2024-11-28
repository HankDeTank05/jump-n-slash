#ifndef PLAYER_H
#define PLAYER_H

// language includes
#include <map>
#include <list>

// engine includes
#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/InputObject.h"
#include "../Engine Code/AlarmObject.h"
#include "../Engine Code/CollisionObject.h"
#include "../Engine Code/Subject.h"
#include "../Engine Code/AnimationComponent.h"
#include "../Engine Code/ControlScheme.h"

// game includes
#include "Actor.h"

// forward declarations
class PlayerMoveState;
class PlayerControlStrategy;
class LevelMap;
class RoomData;
class Sword;

class Player : public Actor, public Subject
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
	virtual void Alarm1() override;

	// collision stuff
	virtual void OnCollisionEnter(CollisionObject* pOther) override;
	virtual void OnCollisionDuring(CollisionObject* pOther) override;
	virtual void OnCollisionExit(CollisionObject* pOther) override;

	// gameobject stuff
	virtual void OnSceneEntry() override;
	virtual void OnSceneExit() override;

private: // player accessors. for selective access only (thru attorney)
	friend class PlayerAttorney;
	bool IsApplyGravity();
	bool IsReceivingSlashInput();
	bool IsAttacking();

private: // player mutators. for selective access only (thru attorney)

	// position and movement

	void ProcessInputs(float deltaTime);
	void SetControls(ControlScheme ctrl);
	void ApplyGravity(float deltaTime);

	void SetWalk(float direction);
	void SetJump(bool enabled);
	void SetSlash(bool enabled);

	// other

	void SetCurrentRoom(RoomData* pCurrentRoom);
	void BeginSlashAtk();

	// animation

	void SetAnimationIdle();
	void SetAnimationWalk();
	void SetAnimationJump();
	void SetAnimationFall();
	void SetAnimationAttack();

private: // Member variables
	PlayerControlStrategy* pCtrlStrat;
	const PlayerMoveState* pCurrentState; // the current movement state
	const PlayerMoveState* pPrevState; // the move state during the previous frame
	Sword* pSword;
	sf::Vector2f respawnPoint; // where the player will respawn after dying
	float inputWalkDir; // float in range [-1, 1] indicating which direction to walk and how fast
	bool inputReceivedJump; // flag indicating if the jump input is currently being received
	bool inputReceivedSlashAtk; // flag indicating if the slash attack input is currently being received
	bool applyGravity; // flag indicating if gravity should be applied
	bool attacking; // flag indicating if we're currently attacking
	float jumpHoldTime; // the amount of time the jump button has been held for
};

#endif