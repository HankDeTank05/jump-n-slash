#include "PlayerStateWalking.h"

#include <array>

#include "../Engine Code/Visualizer.h"

#include "PlayerFSM.h"
#include "PlayerAttorney.h"
#include "Constants.h"
#include "LevelMap.h"
#include "LevelTile.h"

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
	// code goes here
}

void PlayerStateWalking::Update(Player* pPlayer, float deltaTime) const
{
	if (PlayerAttorney::State::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::State::RaycastRight(pPlayer, deltaTime);
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::State::RaycastLeft(pPlayer, deltaTime);
	}
}

const PlayerMoveState* PlayerStateWalking::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y < 0.0f) {
		pNextState = &PlayerFSM::jumping;
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).y > 0.0f) {
		pNextState = &PlayerFSM::falling;
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x == 0.0f) {
		pNextState = &PlayerFSM::idle;
	}

	return pNextState;
}
