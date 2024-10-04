#include "PlayerStateFalling.h"

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

	// logic goes here

	return pNextState;
}
