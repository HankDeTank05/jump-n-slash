#include "SwordStateSwing.h"

// language includes
#include <iostream>

// game includes
#include "GameDebugFlags.h"
#include "SwordFSM.h"
#include "SwordAttorney.h"

void SwordStateSwing::Enter(Sword* pSword) const
{
	if (DEBUG_SWORD_STATE) std::cout << "Entered SwordStateSwing" << std::endl;

	SwordAttorney::StateAccess::RequestCollisionRegistration(pSword);
	SwordAttorney::StateAccess::SetAnimationSwing(pSword);
}

void SwordStateSwing::Update(Sword* pSword, float deltaTime) const
{
	// do nothing (yet)
}

const SwordState* SwordStateSwing::GetNextState(Sword* pSword) const
{
	const SwordState* pNextState = this;

	if (SwordAttorney::StateAccess::IsAttacking(pSword) == false)
	{
		SwordAttorney::StateAccess::RequestCollisionDeregistration(pSword);
		pNextState = &SwordFSM::idle;
	}

	return pNextState;
}
