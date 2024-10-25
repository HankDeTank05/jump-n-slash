#include "Sword.h"

#include <iostream>

#include "../Engine Code/AnimationComponent.h"
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"

#include "PlayerAttorney.h"
#include "SwordFSM.h"
#include "DebugFlags.h"
#include "Constants.h"
#include "PlayerAttorney.h"

Sword::Sword(Player* _pPlayer)
	: pPlayer(_pPlayer),
	playerPosOffset(TILE_SIZE_F, 0.f),
	pos(PlayerAttorney::SwordAccess::GetPos(pPlayer)),
	pCurrentState(&SwordFSM::idle),
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

	RequestUpdateRegistration();
	RequestDrawRegistration();
	SetCollisionSprite(pSprite, VolumeType::AABB);
	SetCollidableGroup<Sword>();
	RequestCollisionRegistration();
}

Sword::~Sword()
{
	delete pAnimComp;
}

void Sword::Update(float deltaTime)
{
	pPrevState = pCurrentState;
	pCurrentState = pCurrentState->GetNextState(this);

	pSprite = pAnimComp->GetCurrentFrame();

	pos = PlayerAttorney::SwordAccess::GetPos(pPlayer) + playerPosOffset;
	pSprite->setPosition(pos);
}

void Sword::Draw()
{
	Render(*pSprite);
}

void Sword::OnCollisionEnter(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Sword has entered collision" << std::endl;
}

void Sword::OnCollisionDuring(CollisionObject* pOther)
{
	// do nothing (yet)
}

void Sword::OnCollisionExit(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Sword has exited collision" << std::endl;
}

void Sword::SetAnimationIdle()
{
	pAnimComp->SetAnimation("idle");
}

void Sword::SetAnimationSwing()
{
	pAnimComp->SetAnimation("swing");
}
