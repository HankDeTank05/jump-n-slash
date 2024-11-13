#ifndef PLAYER_ACTION_STATE_NONE_H
#define PLAYER_ACTION_STATE_NONE_H

// game includes
#include "PlayerActionState.h"

class PlayerActionStateNone : public PlayerActionState
{
public:
	PlayerActionStateNone() = default;
	PlayerActionStateNone(const PlayerActionStateNone& pasn) = delete;
	PlayerActionStateNone& operator=(const PlayerActionStateNone& pasn) = delete;
	virtual ~PlayerActionStateNone() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerActionState* GetNextState(Player* pPlayer) const override;
};

#endif