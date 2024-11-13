#ifndef PLAYER_ACTION_STATE_DREAM_ATK_H
#define PLAYER_ACTION_STATE_DREAM_ATK_H

// game includes
#include "PlayerActionState.h"

class PlayerActionStateDreamAtk : public PlayerActionState
{
public:
	PlayerActionStateDreamAtk() = default;
	PlayerActionStateDreamAtk(const PlayerActionStateDreamAtk& passa) = delete;
	PlayerActionStateDreamAtk& operator=(const PlayerActionStateDreamAtk& passa) = delete;
	virtual ~PlayerActionStateDreamAtk() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerActionState* GetNextState(Player* pPlayer) const override;
};

#endif