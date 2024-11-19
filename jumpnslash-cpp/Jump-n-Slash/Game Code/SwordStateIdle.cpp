#include "SwordStateIdle.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"
#include "SwordFSM.h"

SwordStateIdle::SwordStateIdle(const SwordStateIdle& ssi)
{
	// do nothing
}

void SwordStateIdle::Enter(Sword* pSword) const
{
	if (DEBUG_SWORD_STATE) std::cout << "Entered SwordStateIdle" << std::endl;

	// deregister for collision???
}

void SwordStateIdle::Update(Sword* pSword, float deltaTime) const
{
	// do nothing (yet)
}

const SwordState* SwordStateIdle::GetNextState(Sword* pSword) const
{
	const SwordState* pNextState = this;

	// TODO: sword state change logic goes here

	return pNextState;
}
