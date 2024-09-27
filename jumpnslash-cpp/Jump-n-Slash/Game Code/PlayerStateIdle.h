#ifndef PLAYER_STATE_IDLE_H
#define PLAYER_STATE_IDLE_H

#include "PlayerMoveState.h"

class PlayerStateIdle : public PlayerMoveState
{
public:
	PlayerStateIdle();
	PlayerStateIdle(const PlayerStateIdle& psi);
	PlayerStateIdle& operator=(const PlayerStateIdle& psi);
	virtual ~PlayerStateIdle();

	virtual void Enter(Player* pPlayer) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif