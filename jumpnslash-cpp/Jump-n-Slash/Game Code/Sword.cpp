#include "Sword.h"

// language includes
#include <iostream>

// engine includes
#include "../Engine Code/AnimationComponent.h"
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/Sprite.h"

// game includes
#include "PlayerAttorney.h"
#include "SwordFSM.h"
#include "GameDebugFlags.h"
#include "Constants.h"
#include "Player.h"

Sword::Sword(Player* _pPlayer)
	: pPlayer(_pPlayer),
	playerPosOffset(TILE_SIZE_F, 0.f),
	pos(PlayerAttorney::SwordAccess::GetPos(pPlayer)),
	pCurrentState(&SwordFSM::idle),
	pPrevState(nullptr),
	pSprite(nullptr),
	pAnimComp(new AnimationComponent()),
	attack(false)
{
	pAnimComp->DefineAnimation("idle", AnimationManager::GetAnimation("sword idle"));
	pAnimComp->DefineAnimation("swing", AnimationManager::GetAnimation("sword swing"));

	pAnimComp->SetAnimation("idle");
	pSprite = pAnimComp->GetCurrentFrame();

	RequestUpdateRegistration();
	RequestDrawRegistration();
	SetCollisionSprite(pSprite, VolumeType::AABB);
	SetCollisionObjectGroup<Sword>();
	//RequestCollisionRegistration();
}

Sword::~Sword()
{
	delete pAnimComp;
}

void Sword::Update(float deltaTime)
{
	pCurrentState = pCurrentState->GetNextState(this);
	if (pCurrentState != pPrevState)
	{
		pCurrentState->Enter(this);
	}
	if (attack == true)
	{
		attack = false;
	}

	pCurrentState->Update(this, deltaTime);

	pSprite = pAnimComp->GetCurrentFrame();

	pos = PlayerAttorney::SwordAccess::GetPos(pPlayer) + pPlayer->GetConnector("weapon hold");

	// TODO: make this class derive from actor, so it can use the protected function that does this automagically
	float facing = PlayerAttorney::SwordAccess::GetFacing(pPlayer);
	if (facing == 1)
	{
		pSprite->SetOrigin(sf::Vector2f(0.f, 0.f));
	}
	else if (facing == -1)
	{
		pSprite->SetOrigin(sf::Vector2f(TILE_SIZE_F, 0.f));
	}
	else
	{
		assert(false);
	}
	pSprite->SetScale(sf::Vector2f(facing, 1.f));

	pSprite->SetPositionByConnector("hold", pos);
	UpdateCollisionData(pSprite);

	pPrevState = pCurrentState;

	if (DEBUG_CONNECTORS) pSprite->DebugConnectors();
}

void Sword::Draw()
{
	Render(pSprite);
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

void Sword::Attack()
{
	attack = true;
}

bool Sword::IsAttacking()
{
	return attack;
}

void Sword::SetAnimationIdle()
{
	pAnimComp->SetAnimation("idle");
}

void Sword::SetAnimationSwing()
{
	pAnimComp->SetAnimation("swing");
}
