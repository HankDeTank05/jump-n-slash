#include "PlayerStateIdle.h"

// language includes
#include <iostream>

// game includes
#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "DebugFlags.h"

void PlayerStateIdle::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerStateIdle" << std::endl;

	PlayerAttorney::StateAccess::SetAnimationIdle(pPlayer);
}

void PlayerStateIdle::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::StateAccess::ProcessInputs(pPlayer, deltaTime);
	
	if (PlayerAttorney::StateAccess::IsApplyGravity(pPlayer))
	{
		PlayerAttorney::StateAccess::ApplyGravity(pPlayer, deltaTime);
	}

	PlayerAttorney::StateAccess::RaycastDown(pPlayer);
}

const PlayerMoveState* PlayerStateIdle::GetNextState(Player* pPlayer) const
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
	else if (PlayerAttorney::StateAccess::GetPosDelta(pPlayer).x != 0.0f)
	{
		pNextState = &PlayerFSM::walking;
	}

	return pNextState;
}
