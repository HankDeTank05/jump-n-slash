#ifndef PLAYER_STATE_FALLING_H
#define PLAYER_STATE_FALLING_H

#include "PlayerMoveState.h"

class PlayerStateFalling : public PlayerMoveState
{
public:
	PlayerStateFalling();
	PlayerStateFalling(const PlayerStateFalling& psf);
	PlayerStateFalling& operator=(const PlayerStateFalling& psf);
	virtual ~PlayerStateFalling();

	virtual void Enter(Player* pPlayer) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif