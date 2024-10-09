#include "PlayerStateJumping.h"

#include "PlayerFSM.h"
#include "PlayerAttorney.h"

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
	// code goes here
}

void PlayerStateJumping::Update(Player* pPlayer, float deltaTime) const
{
	assert(false);
}

const PlayerMoveState* PlayerStateJumping::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y > 0.0f) {
		pNextState = &PlayerFSM::falling;
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).y == 0.0f) { // Would prefer to check if the player is grounded
		if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f) {
			pNextState = &PlayerFSM::walking; // Not technically possible at the moment
		}
		else { // If this statement is reached, then the player is not moving vertically or horizontally
			pNextState = &PlayerFSM::idle; // Not technically possible at the moment
		}
	}
	return pNextState;
}
