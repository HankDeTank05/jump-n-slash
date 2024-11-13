#ifndef PLAYER_ACTION_STATE_SLASH_ATK_H
#define PLAYER_ACTION_STATE_SLASH_ATK_H

// game includes
#include "PlayerActionState.h"

class PlayerActionStateSlashAtk : public PlayerActionState
{
public:
	PlayerActionStateSlashAtk() = default;
	PlayerActionStateSlashAtk(const PlayerActionStateSlashAtk& passa) = delete;
	PlayerActionStateSlashAtk& operator=(const PlayerActionStateSlashAtk& passa) = delete;
	virtual ~PlayerActionStateSlashAtk() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerActionState* GetNextState(Player* pPlayer) const override;
};

#endif