#ifndef PLAYER_MOVE_STATE_DREAM_ATK_H
#define PLAYER_MOVE_STATE_DREAM_ATK_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateDreamAtk : public PlayerMoveState
{
public:
	PlayerMoveStateDreamAtk() = default;
	PlayerMoveStateDreamAtk(const PlayerMoveStateDreamAtk& passa) = delete;
	PlayerMoveStateDreamAtk& operator=(const PlayerMoveStateDreamAtk& passa) = delete;
	virtual ~PlayerMoveStateDreamAtk() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif