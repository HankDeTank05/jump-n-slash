#ifndef PLAYER_MOVE_STATE_JUMPING_H
#define PLAYER_MOVE_STATE_JUMPING_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateJumping : public PlayerMoveState
{
public:
	PlayerMoveStateJumping() = default;
	PlayerMoveStateJumping(const PlayerMoveStateJumping& psj) = delete;
	PlayerMoveStateJumping& operator=(const PlayerMoveStateJumping& psj) = delete;
	virtual ~PlayerMoveStateJumping() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif