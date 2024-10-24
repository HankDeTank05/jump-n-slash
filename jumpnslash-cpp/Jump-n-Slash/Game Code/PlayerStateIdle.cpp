#include "PlayerStateIdle.h"

#include <iostream>

#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "DebugFlags.h"

PlayerStateIdle::PlayerStateIdle()
{
	// do nothing
}

PlayerStateIdle::PlayerStateIdle(const PlayerStateIdle& psi)
{
	// do nothing
}

PlayerStateIdle& PlayerStateIdle::operator=(const PlayerStateIdle& psi)
{
	return *this;
}

PlayerStateIdle::~PlayerStateIdle()
{
	// do nothing
}

void PlayerStateIdle::Enter(Player* pPlayer) const
{
	if (DEBUG_PLAYER_STATE) std::cout << "Entered PlayerStateIdle" << std::endl;

	PlayerAttorney::State::SetAnimationIdle(pPlayer);
}

void PlayerStateIdle::Update(Player* pPlayer, float deltaTime) const
{
	PlayerAttorney::State::ProcessInputs(pPlayer, deltaTime);
	PlayerAttorney::State::ApplyGravity(pPlayer, deltaTime);
	PlayerAttorney::State::RaycastDown(pPlayer, deltaTime);
}

const PlayerMoveState* PlayerStateIdle::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerFSM::jumping;
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).y > 0.0f)
	{
		pNextState = &PlayerFSM::falling; // Not technically possible at the moment
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f)
	{
		pNextState = &PlayerFSM::walking;
	}

	return pNextState;
}
