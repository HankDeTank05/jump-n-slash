#include "PlayerActionStateSlashAtk.h"

// language includes
#include <iostream>

// game includes
#include "DebugFlags.h"

void PlayerActionStateSlashAtk::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerActionStateSlashAtk" << std::endl;

	assert(false); // TODO: set slash atk animation (based on equipped slash atk dreamcatcher?)
}

void PlayerActionStateSlashAtk::Update(Player* pPlayer, float deltaTime) const
{
	assert(false); // TODO: implement update behavior
}

const PlayerActionState* PlayerActionStateSlashAtk::GetNextState(Player* pPlayer) const
{
	const PlayerActionState* pNextState = this;

	assert(false); // TODO: implement state change logic

	return pNextState;
}
