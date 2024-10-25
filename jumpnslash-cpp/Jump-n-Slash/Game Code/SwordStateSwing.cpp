#include "SwordStateSwing.h"

#include <iostream>

#include "DebugFlags.h"

void SwordStateSwing::Enter(Sword* pSword) const
{
	if (DEBUG_SWORD_STATE) std::cout << "Entered SwordStateSwing" << std::endl;

	// register for collision???
}

void SwordStateSwing::Update(Sword* pSword, float deltaTime) const
{
	// do nothing (yet)
}

const SwordState* SwordStateSwing::GetNextState(Sword* pSword) const
{
	const SwordState* pNextState = this;

	// TODO: sword state change logic goes here

	return pNextState;
}
