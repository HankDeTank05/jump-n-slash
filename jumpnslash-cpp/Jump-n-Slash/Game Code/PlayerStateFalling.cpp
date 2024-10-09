#include "PlayerStateFalling.h"

#include "PlayerFSM.h"
#include "PlayerAttorney.h"

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
	// code goes here
}

void PlayerStateFalling::Update(Player* pPlayer, float deltaTime) const
{
	assert(false);
}

const PlayerMoveState* PlayerStateFalling::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y < 0.0f) {
		pNextState = &PlayerFSM::jumping; // Not technically possible at the moment
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).y == 0.0f) { // Would prefer to check if the player is grounded
		if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f) {
			pNextState = &PlayerFSM::walking;
		}
		else { // If this statement is reached, then the player is not moving vertically or horizontally
			pNextState = &PlayerFSM::idle;
		}
	}

	return pNextState;
}
