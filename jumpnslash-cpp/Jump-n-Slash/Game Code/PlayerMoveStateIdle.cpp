#include "PlayerMoveStateIdle.h"

// language includes
#include <iostream>

// game includes
#include "PlayerMoveFSM.h"
#include "PlayerAttorney.h"
#include "GameDebugFlags.h"

void PlayerMoveStateIdle::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_MOVE_STATE) std::cout << "Entered PlayerMoveStateIdle" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationIdle(pPlayer);
}

void PlayerMoveStateIdle::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}

	PlayerAttorney::StateAccess::RaycastDown(pPlayer);
}

const PlayerMoveState* PlayerMoveStateIdle::GetNextState(Player* pPlayer) const
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
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x != 0.0f)
	{
		pNextState = &PlayerMoveFSM::walking;
	}

	return pNextState;
}
