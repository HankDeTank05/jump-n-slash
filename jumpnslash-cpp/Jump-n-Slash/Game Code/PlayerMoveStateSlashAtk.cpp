#include "PlayerMoveStateSlashAtk.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"

void PlayerMoveStateSlashAtk::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerMoveStateSlashAtk" << std::endl;

	assert(false); // TODO: set slash atk animation (based on equipped slash atk dreamcatcher?)
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
