#include "PlayerMoveStateDashing.h"

// language includes
#include <iostream>

// game includes
#include "DebugFlags.h"
#include "PlayerAttorney.h"

void PlayerMoveStateDashing::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_MOVE_STATE) std::cout << "Entered PlayerMoveStateDashing" << std::endl;

	// TODO: set dashing animation
}

void PlayerMoveStateDashing::Update(Player* pPlayer, float deltaTime) const
{
	assert(false); // TODO: implement update behavior
}

const PlayerMoveState* PlayerMoveStateDashing::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	assert(false); // TODO: implement state change logic

	return pNextState;
}
