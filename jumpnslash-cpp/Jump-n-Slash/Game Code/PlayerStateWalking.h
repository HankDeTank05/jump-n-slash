#ifndef PLAYER_STATE_WALKING_H
#define PLAYER_STATE_WALKING_H

#include "PlayerMoveState.h"

class PlayerStateWalking : public PlayerMoveState
{
public:
	PlayerStateWalking();
	PlayerStateWalking(const PlayerStateWalking& psw);
	PlayerStateWalking& operator=(const PlayerStateWalking& psw);
	virtual ~PlayerStateWalking();

	virtual void Enter(Player* pPlayer) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif