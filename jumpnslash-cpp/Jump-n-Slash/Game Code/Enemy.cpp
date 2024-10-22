#include "Enemy.h"

#include "Constants.h"

#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"

Enemy::Enemy()
	: pos(10 * TILE_SIZE_F, 18 * TILE_SIZE_F),
	posDelta(0.f, 0.f),
	pSprite(nullptr),
	animComp()
{
	AnimationSet* pAnimSet = new AnimationSet();

	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("enemy idle"));

	animComp.DefineAnimationSet(pAnimSet);
	animComp.SetAnimation("idle");

	RequestUpdateRegistration();
	RequestDrawRegistration();

	SetCollidableGroup<Enemy>();
	pSprite = animComp.GetCurrentFrame();
	SetCollisionSprite(pSprite, VolumeType::AABB);
	RequestCollisionRegistration();
}

Enemy::~Enemy()
{
	// do nothing
}

void Enemy::Update(float deltaTime)
{
	pSprite = animComp.GetCurrentFrame();
	pSprite->setPosition(pos);
	UpdateCollisionData(pSprite);
}

void Enemy::Draw()
{
	assert(pSprite != nullptr);
	Render(*pSprite);
}

void Enemy::Collision(Player* pPlayer)
{
	// TODO: make a debug flag for this
	std::cout << "Enemy::Collision(Player* pPlayer) function call" << std::endl;
}
