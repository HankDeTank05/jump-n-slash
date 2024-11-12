#ifndef PLAYER_STATE_WALKING_H
#define PLAYER_STATE_WALKING_H

// game includes
#include "PlayerMoveState.h"

class PlayerStateWalking : public PlayerMoveState
{
public:
	PlayerStateWalking() = default;
	PlayerStateWalking(const PlayerStateWalking& psw) = delete;
	PlayerStateWalking& operator=(const PlayerStateWalking& psw) = delete;
	virtual ~PlayerStateWalking() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif