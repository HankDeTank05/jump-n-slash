#include "SwordStateIdle.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"
#include "SwordFSM.h"
#include "SwordAttorney.h"

SwordStateIdle::SwordStateIdle(const SwordStateIdle& ssi)
{
	// do nothing
}

void SwordStateIdle::Enter(Sword* pSword) const
{
	if (DEBUG_SWORD_STATE) std::cout << "Entered SwordStateIdle" << std::endl;

	SwordAttorney::StateAccess::SetAnimationIdle(pSword);
}

void SwordStateIdle::Update(Sword* pSword, float deltaTime) const
{
	// do nothing (yet)
}

const SwordState* SwordStateIdle::GetNextState(Sword* pSword) const
{
	const SwordState* pNextState = this;

	if (SwordAttorney::StateAccess::IsAttacking(pSword))
	{
		pNextState = &SwordFSM::swing;
	}

	return pNextState;
}
