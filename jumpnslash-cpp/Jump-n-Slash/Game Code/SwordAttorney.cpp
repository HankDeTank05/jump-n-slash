#include "SwordAttorney.h"

// game includes
#include "Sword.h"

bool SwordAttorney::StateAccess::IsAttacking(Sword* pSword)
{
	return pSword->IsAttacking();
}

void SwordAttorney::StateAccess::RequestCollisionRegistration(Sword* pSword)
{
	pSword->RequestCollisionRegistration();
}

void SwordAttorney::StateAccess::RequestCollisionDeregistration(Sword* pSword)
{
	pSword->RequestCollisionDeregistration();
}

void SwordAttorney::StateAccess::SetAnimationIdle(Sword* pSword)
{
	pSword->SetAnimationIdle();
}

void SwordAttorney::StateAccess::SetAnimationSwing(Sword* pSword)
{
	pSword->SetAnimationSwing();
}

void SwordAttorney::PlayerAccess::Attack(Sword* pSword)
{
	pSword->Attack();
}
