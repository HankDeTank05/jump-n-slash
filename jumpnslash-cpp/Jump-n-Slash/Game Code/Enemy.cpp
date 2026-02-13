#include "Enemy.h"

// engine includes
#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/Sprite.h"

// game includes
#include "Constants.h"
#include "GameDebugFlags.h"

Enemy::Enemy()
	: pos(10 * TILE_SIZE_F, 18 * TILE_SIZE_F),
	posDelta(0.f, 0.f),
	pSprite(nullptr),
	animComp()
{
	animComp.DefineAnimation("idle", AnimationManager::GetAnimation("enemy idle"));

	animComp.SetAnimation("idle");

	RequestUpdateRegistration();
	RequestDrawRegistration();

	SetCollisionObjectGroup<Enemy>();
	pSprite = animComp.GetCurrentFrame();
	SetCollisionSprite(pSprite, VolumeType::BSphere);
	RequestCollisionRegistration();
}

Enemy::~Enemy()
{
	// do nothing
}

void Enemy::Update(float deltaTime)
{
	pSprite = animComp.GetCurrentFrame();
	pSprite->SetPosition(pos);
	UpdateCollisionData(pSprite);
	if (DEBUG_CONNECTORS) pSprite->DebugConnectors();
}

void Enemy::Draw()
{
	assert(pSprite != nullptr);
	Render(pSprite);
}

void Enemy::OnCollisionEnter(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Enemy has entered collision" << std::endl;
}

void Enemy::OnCollisionDuring(CollisionObject* pOther)
{
	// do nothing
}

void Enemy::OnCollisionExit(CollisionObject* pOther)
{
	if (DEBUG_COLLISION) std::cout << "Enemy has exited collision" << std::endl;
}
