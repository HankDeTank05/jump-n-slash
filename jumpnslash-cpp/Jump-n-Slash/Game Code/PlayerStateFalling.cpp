#include "PlayerStateFalling.h"

#include <iostream>

#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "DebugFlags.h"

PlayerStateFalling::PlayerStateFalling()
{
	// do nothing
}

PlayerStateFalling::PlayerStateFalling(const PlayerStateFalling& psf)
{
	// do nothing
}

PlayerStateFalling& PlayerStateFalling::operator=(const PlayerStateFalling& psf)
{
	return *this;
}

PlayerStateFalling::~PlayerStateFalling()
{
	// do nothing
}

void PlayerStateFalling::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerStateFalling" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationFall(pPlayer);
}

void PlayerStateFalling::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);

	// Player can move left or right while falling
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

const PlayerMoveState* PlayerStateFalling::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerFSM::jumping; // Not technically possible at the moment
	}
	else if (PlayerAttorney::StateAccess::IsGrounded(pPlayer))
	{
		if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x != 0.0f)
		{
			pNextState = &PlayerFSM::walking;
		}
		else // If this statement is reached, then the player is not moving vertically or horizontally
		{
			pNextState = &PlayerFSM::idle;
		}
	}

	return pNextState;
}
