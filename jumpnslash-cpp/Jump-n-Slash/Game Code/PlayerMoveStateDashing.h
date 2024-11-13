#ifndef PLAYER_MOVE_STATE_DASHING_H
#define PLAYER_MOVE_STATE_DASHING_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateDashing : public PlayerMoveState
{
public:
	PlayerMoveStateDashing() = default;
	PlayerMoveStateDashing(const PlayerMoveStateDashing& psd) = delete;
	PlayerMoveStateDashing& operator=(const PlayerMoveStateDashing& psd) = delete;
	virtual ~PlayerMoveStateDashing() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif