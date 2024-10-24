#include "PlayerStateJumping.h"

#include <iostream>

#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "DebugFlags.h"

PlayerStateJumping::PlayerStateJumping()
{
	// do nothing
}

PlayerStateJumping::PlayerStateJumping(const PlayerStateJumping& psj)
{
	// do nothing
}

PlayerStateJumping& PlayerStateJumping::operator=(const PlayerStateJumping& psj)
{
	return *this;
}

PlayerStateJumping::~PlayerStateJumping()
{
	// do nothing
}

void PlayerStateJumping::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerStateJumping" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationJump(pPlayer);
}

void PlayerStateJumping::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	
	// Player can move left or right while jumping
	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::StateAccess::RaycastRight(pPlayer, deltaTime);
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::StateAccess::RaycastLeft(pPlayer, deltaTime);
	}

	PlayerAttorney::StateAccess::RaycastUp(pPlayer, deltaTime);
}

const PlayerMoveState* PlayerStateJumping::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y > 0.0f)
	{
		pNextState = &PlayerFSM::falling;
	}
	else if (PlayerAttorney::StateAccess::IsGrounded(pPlayer))
	{ 
		if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x != 0.0f)
		{
			pNextState = &PlayerFSM::walking; // Not technically possible at the moment
		}
		else // If this statement is reached, then the player is not moving vertically or horizontally
		{ 
			pNextState = &PlayerFSM::idle; // Not technically possible at the moment
		}
	}
	return pNextState;
}
