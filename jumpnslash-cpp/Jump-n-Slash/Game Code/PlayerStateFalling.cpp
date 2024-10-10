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
	PlayerAttorney::State::RaycastDown(pPlayer, deltaTime);
	
	// Player can move left or right while falling
	if (PlayerAttorney::State::GetPosDelta(pPlayer).x > 0) // check for map collision moving right
	{
		PlayerAttorney::State::RaycastRight(pPlayer, deltaTime);
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).x < 0) // check for map collision moving left
	{
		PlayerAttorney::State::RaycastLeft(pPlayer, deltaTime);
	}
}

const PlayerMoveState* PlayerStateFalling::GetNextState(Player* pPlayer) const
{
	const PlayerMoveState* pNextState = this;

	if (PlayerAttorney::State::GetPosDelta(pPlayer).y < 0.0f)
	{
		pNextState = &PlayerFSM::jumping; // Not technically possible at the moment
	}
	else if (PlayerAttorney::State::GetPosDelta(pPlayer).y == 0.0f) // Would prefer to check if the player is grounded
	{
		if (PlayerAttorney::State::GetPosDelta(pPlayer).x != 0.0f)
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
