#include "PlayerStateWalking.h"

// language includes
#include <array>
#include <iostream>

// engine includes
//#include "../Engine Code/Visualizer.h"

// game includes
#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "Constants.h"
#include "LevelMap.h"
#include "LevelTile.h"
#include "DebugFlags.h"

void PlayerStateWalking::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerSateWalking" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationWalk(pPlayer);
}

void PlayerStateWalking::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}
	else
	{
		//assert(false); // if you reach this statement, then you fucked up bitch (or ur in space idfk)
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

const PlayerMoveState* PlayerStateWalking::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerFSM::jumping;
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y > 0.0f)
	{
		pNextState = &PlayerFSM::falling;
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x == 0.0f)
	{
		pNextState = &PlayerFSM::idle;
	}

	return pNextState;
}
