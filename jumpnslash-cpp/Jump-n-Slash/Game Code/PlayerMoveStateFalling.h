#ifndef PLAYER_MOVE_STATE_FALLING_H
#define PLAYER_MOVE_STATE_FALLING_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateFalling : public PlayerMoveState
{
public:
	PlayerMoveStateFalling() = default;
	PlayerMoveStateFalling(const PlayerMoveStateFalling& psf) = delete;
	PlayerMoveStateFalling& operator=(const PlayerMoveStateFalling& psf) = delete;
	virtual ~PlayerMoveStateFalling() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif