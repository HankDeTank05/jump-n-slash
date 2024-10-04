#ifndef PLAYER_STATE_JUMPING_H
#define PLAYER_STATE_JUMPING_H

#include "PlayerMoveState.h"

class PlayerStateJumping : public PlayerMoveState
{
public:
	PlayerStateJumping();
	PlayerStateJumping(const PlayerStateJumping& psj);
	PlayerStateJumping& operator=(const PlayerStateJumping& psj);
	virtual ~PlayerStateJumping();

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif