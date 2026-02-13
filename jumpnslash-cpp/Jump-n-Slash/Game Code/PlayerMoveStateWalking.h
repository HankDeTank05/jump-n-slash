#ifndef PLAYER_MOVE_STATE_WALKING_H
#define PLAYER_MOVE_STATE_WALKING_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateWalking : public PlayerMoveState
{
public:
	PlayerMoveStateWalking() = default;
	PlayerMoveStateWalking(const PlayerMoveStateWalking& psw) = delete;
	PlayerMoveStateWalking& operator=(const PlayerMoveStateWalking& psw) = delete;
	virtual ~PlayerMoveStateWalking() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif