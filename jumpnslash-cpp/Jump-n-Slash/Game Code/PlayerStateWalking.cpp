#include "PlayerStateWalking.h"

#include <array>
#include <iostream>

#include "../Engine Code/Visualizer.h"

#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "Constants.h"
#include "LevelMap.h"
#include "LevelTile.h"
#include "DebugFlags.h"

PlayerStateWalking::PlayerStateWalking()
{
	// do nothing
}

PlayerStateWalking::PlayerStateWalking(const PlayerStateWalking& psw)
{
	// do nothing
}

PlayerStateWalking& PlayerStateWalking::operator=(const PlayerStateWalking& psw)
{
	return *this;
}

PlayerStateWalking::~PlayerStateWalking()
{
	// do nothing
}

void PlayerStateWalking::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerSateWalking" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationWalk(pPlayer);
}

void PlayerStateWalking::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::StateAccess::RaycastRight(pPlayer, deltaTime);
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::StateAccess::RaycastLeft(pPlayer, deltaTime);
	}

	PlayerAttorney::StateAccess::RaycastDown(pPlayer, deltaTime);
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
