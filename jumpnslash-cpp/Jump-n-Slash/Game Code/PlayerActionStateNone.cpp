#include "PlayerActionStateNone.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"

void PlayerActionStateNone::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_ACTION_STATE) std::cout << "Entered PlayerActionStateNone" << std::endl;
	
	assert(false); // TODO: set animation based on move state
}

void PlayerActionStateNone::Update(Player* pPlayer, float deltaTime) const
{
	assert(false); // TODO: implement update behavior
}

const PlayerActionState* PlayerActionStateNone::GetNextState(Player* pPlayer) const
{
	const PlayerActionState* pNextState = this;

	assert(false); // TODO: implement state change logic

	return pNextState;
}
