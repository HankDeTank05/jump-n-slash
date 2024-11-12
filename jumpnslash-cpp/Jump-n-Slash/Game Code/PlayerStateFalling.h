#ifndef PLAYER_STATE_FALLING_H
#define PLAYER_STATE_FALLING_H

// game includes
#include "PlayerMoveState.h"

class PlayerStateFalling : public PlayerMoveState
{
public:
	PlayerStateFalling() = default;
	PlayerStateFalling(const PlayerStateFalling& psf) = delete;
	PlayerStateFalling& operator=(const PlayerStateFalling& psf) = delete;
	virtual ~PlayerStateFalling() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif