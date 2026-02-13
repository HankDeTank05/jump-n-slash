#include "PlayerMoveStateDreamAtk.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"

void PlayerMoveStateDreamAtk::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerMoveStateDreamAtk" << std::endl;

	assert(false); // TODO: set slash atk animation (based on equipped slash atk dreamcatcher?)
}

void PlayerMoveStateDreamAtk::Update(Player* pPlayer, float deltaTime) const
{
	assert(false); // TODO: implement update behavior
}

const PlayerMoveState* PlayerMoveStateDreamAtk::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	assert(false); // TODO: implement state change logic

	return pNextState;
}
