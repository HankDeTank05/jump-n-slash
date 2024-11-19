#include "PlayerMoveStateFalling.h"

// language includes
#include <iostream>

// game includes
#include "PlayerMoveFSM.h"
#include "PlayerAttorney.h"
#include "GameDebugFlags.h"

void PlayerMoveStateFalling::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_MOVE_STATE) std::cout << "Entered PlayerMoveStateFalling" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationFall(pPlayer);
}

void PlayerMoveStateFalling::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}

	// Player can move left or right while falling
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

const PlayerMoveState* PlayerMoveStateFalling::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	// TODO: update state change logic to include PlayerMoveStateDashing (if applicable)

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerMoveFSM::jumping; // Not technically possible at the moment
	}
	else if (PlayerAttorney::StateAccess::IsGrounded(pPlayer))
	{
		if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x != 0.0f)
		{
			pNextState = &PlayerMoveFSM::walking;
		}
		else // If this statement is reached, then the player is not moving vertically or horizontally
		{
			pNextState = &PlayerMoveFSM::idle;
		}
	}

	return pNextState;
}
