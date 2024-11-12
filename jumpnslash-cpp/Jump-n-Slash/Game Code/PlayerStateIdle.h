#ifndef PLAYER_STATE_IDLE_H
#define PLAYER_STATE_IDLE_H

// game includes
#include "PlayerMoveState.h"

class PlayerStateIdle : public PlayerMoveState
{
public:
	PlayerStateIdle() = default;
	PlayerStateIdle(const PlayerStateIdle& psi) = delete;
	PlayerStateIdle& operator=(const PlayerStateIdle& psi) = delete;
	virtual ~PlayerStateIdle() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif