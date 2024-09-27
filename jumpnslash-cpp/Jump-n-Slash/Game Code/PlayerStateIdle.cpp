#include "PlayerStateIdle.h"

#include "PlayerFSM.h"
#include "PlayerAttorney.h"

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
	// code goes here
}

const PlayerMoveState* PlayerStateIdle::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDeltaY(pPlayer) < 0.0f)
	{
		pNextState = &PlayerFSM::jumping;
	}
	else if (PlayerAttorney::State::GetPosDeltaY(pPlayer) > 0.0f)
	{
		pNextState = &PlayerFSM::falling;
	}
	else if (PlayerAttorney::State::GetPosDeltaX(pPlayer) != 0.0f)
	{
		pNextState = &PlayerFSM::walking;
	}

	return pNextState;
}
