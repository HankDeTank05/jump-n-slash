#include "Sword.h"

#include "../Engine Code/AnimationComponent.h"
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"

#include "PlayerAttorney.h"

Sword::Sword(Player* _pPlayer)
	: pPlayer(_pPlayer),
	pos(PlayerAttorney::SwordAccess::GetPos(pPlayer)),
	pCurrentState(nullptr),
	pPrevState(nullptr),
	pSprite(nullptr),
	pAnimComp(new AnimationComponent())
{
	AnimationSet* pAnimSet = new AnimationSet();
	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("sword idle"));
	pAnimSet->AddAnimation("swing", AnimationManager::GetAnimation("sword swing"));
	pAnimComp->DefineAnimationSet(pAnimSet);

	pAnimComp->SetAnimation("idle");
	pSprite = pAnimComp->GetCurrentFrame();
}
