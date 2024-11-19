#include "PlayerMoveStateWalking.h"

// language includes
#include <array>
#include <iostream>

// game includes
#include "PlayerMoveFSM.h"
#include "PlayerAttorney.h"
#include "Constants.h"
#include "LevelMap.h"
#include "LevelTile.h"
#include "GameDebugFlags.h"

void PlayerMoveStateWalking::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_MOVE_STATE) std::cout << "Entered PlayerMoveStateWalking" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationWalk(pPlayer);
}

void PlayerMoveStateWalking::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::StateAccess::RaycastRight(pPlayer);
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::StateAccess::RaycastLeft(pPlayer);
	}

	PlayerAttorney::StateAccess::RaycastDown(pPlayer);
}

const PlayerMoveState* PlayerMoveStateWalking::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	// TODO: update state change logic to include PlayerMoveStateDashing (if applicable)

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerMoveFSM::jumping;
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y > 0.0f)
	{
		pNextState = &PlayerMoveFSM::falling;
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x == 0.0f)
	{
		pNextState = &PlayerMoveFSM::idle;
	}

	return pNextState;
}
