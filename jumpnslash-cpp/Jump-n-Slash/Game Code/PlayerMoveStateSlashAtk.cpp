#include "PlayerMoveStateSlashAtk.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"
#include "PlayerAttorney.h"

void PlayerMoveStateSlashAtk::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerMoveStateSlashAtk" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationAttack(pPlayer);
}

void PlayerMoveStateSlashAtk::Update(Player* pPlayer, float deltaTime) const
{
	assert(false); // TODO: implement update behavior
}

const PlayerMoveState* PlayerMoveStateSlashAtk::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	assert(false); // TODO: implement state change logic

	return pNextState;
}
