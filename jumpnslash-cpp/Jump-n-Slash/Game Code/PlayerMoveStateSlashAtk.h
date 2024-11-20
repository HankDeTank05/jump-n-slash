#ifndef PLAYER_MOVE_STATE_SLASH_ATK_H
#define PLAYER_MOVE_STATE_SLASH_ATK_H

// game includes
#include "PlayerMoveState.h"

class PlayerMoveStateSlashAtk : public PlayerMoveState
{
public:
	PlayerMoveStateSlashAtk() = default;
	PlayerMoveStateSlashAtk(const PlayerMoveStateSlashAtk& passa) = delete;
	PlayerMoveStateSlashAtk& operator=(const PlayerMoveStateSlashAtk& passa) = delete;
	virtual ~PlayerMoveStateSlashAtk() = default;

	virtual void Enter(Player* pPlayer) const override;
	virtual void Update(Player* pPlayer, float deltaTime) const override;
	virtual const PlayerMoveState* GetNextState(Player* pPlayer) const override;
};

#endif