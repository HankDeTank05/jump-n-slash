#ifndef PLAYER_MOVE_STATE_IDLE_H
#define PLAYER_MOVE_STATE_IDLE_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateIdle : public PlayerMoveState
{
public:
	PlayerMoveStateIdle() = default;
	PlayerMoveStateIdle(const PlayerMoveStateIdle& psi) = delete;
	PlayerMoveStateIdle& operator=(const PlayerMoveStateIdle& psi) = delete;
	virtual ~PlayerMoveStateIdle() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif