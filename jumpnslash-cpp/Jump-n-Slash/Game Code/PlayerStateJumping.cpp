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

	PlayerAttorney::State::SetAnimationJump(pPlayer);
}

void PlayerStateJumping::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::State::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::State::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::State::ApplyGravity(pPlayer, deltaTime);
	}
	
	// Player can move left or right while jumping
	if (PlayerAttorney::State::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::State::RaycastRight(pPlayer);
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::State::RaycastLeft(pPlayer);
	}

	PlayerAttorney::State::RaycastUp(pPlayer);
}

const PlayerMoveState* PlayerStateJumping::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y > 0.0f || PlayerAttorney::State::IsHeadBonked(pPlayer))
	{
		pNextState = &PlayerFSM::falling;
	}
	//else if (PlayerAttorney::State::IsGrounded(pPlayer))
	//{ 
	//	if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f)
	//	{
	//		pNextState = &PlayerFSM::walking; // Not technically possible at the moment
	//	}
	//	else // If this statement is reached, then the player is not moving vertically or horizontally
	//	{ 
	//		pNextState = &PlayerFSM::idle; // Not technically possible at the moment
	//	}
	//}
	return pNextState;
}
