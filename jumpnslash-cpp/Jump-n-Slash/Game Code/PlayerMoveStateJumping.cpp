#include "PlayerMoveStateJumping.h"

// language includes
#include <iostream>

// game includes
#include "PlayerMoveFSM.h"
#include "PlayerAttorney.h"
#include "GameDebugFlags.h"

void PlayerMoveStateJumping::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_MOVE_STATE) std::cout << "Entered PlayerMoveStateJumping" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationJump(pPlayer);
}

void PlayerMoveStateJumping::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}
	
	// Player can move left or right while jumping
	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::StateAccess::RaycastRight(pPlayer);
	}
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::StateAccess::RaycastLeft(pPlayer);
	}

	PlayerAttorney::StateAccess::RaycastUp(pPlayer);
}

const PlayerMoveState* PlayerMoveStateJumping::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	// TODO: update state change logic to include PlayerMoveStateDashing (if applicable)
	
	if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).y > 0.0f || PlayerAttorney::StateAccess::IsHeadBonked(pPlayer))
	{
		pNextState = &PlayerMoveFSM::falling;
	}
	//else if (PlayerAttorney::State::IsGrounded(pPlayer))
	//{ 
	//	if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f)
	//	{
	//		pNextState = &PlayerMoveFSM::walking; // Not technically possible at the moment
	//	}
	//	else // If this statement is reached, then the player is not moving vertically or horizontally
	//	{ 
	//		pNextState = &PlayerMoveFSM::idle; // Not technically possible at the moment
	//	}
	//}
	return pNextState;
}
