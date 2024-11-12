#ifndef PLAYER_STATE_JUMPING_H
#define PLAYER_STATE_JUMPING_H

// game includes
#include "PlayerMoveState.h"

class PlayerStateJumping : public PlayerMoveState
{
public:
	PlayerStateJumping() = default;
	PlayerStateJumping(const PlayerStateJumping& psj) = delete;
	PlayerStateJumping& operator=(const PlayerStateJumping& psj) = delete;
	virtual ~PlayerStateJumping() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif