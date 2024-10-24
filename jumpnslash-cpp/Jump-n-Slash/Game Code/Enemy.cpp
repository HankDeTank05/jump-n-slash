#include "Enemy.h"

#include "Constants.h"

#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"

Enemy::Enemy()
	: pos(10 * TILE_SIZE_F, 18 * TILE_SIZE_F),
	posDelta(0.f, 0.f),
	pSprite(nullptr),
	animComp(),
	rotation(45.f)
{
	AnimationSet* pAnimSet = new AnimationSet();

	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("enemy idle"));

	animComp.DefineAnimationSet(pAnimSet);
	animComp.SetAnimation("idle");

	RequestUpdateRegistration();
	RequestDrawRegistration();

	SetCollidableGroup<Enemy>();
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
	pSprite->setPosition(pos);
	pSprite->setRotation(rotation);
	UpdateCollisionData(pSprite);
}

void Enemy::Draw()
{
	assert(pSprite != nullptr);
	Render(*pSprite);
}

void Enemy::OnCollisionEnter(CollisionObject* pOther)
{
	// TODO: make a debug flag for this
	std::cout << "Enemy has entered collision" << std::endl;
}

void Enemy::OnCollisionDuring(CollisionObject* pOther)
{
	// do nothing
}

void Enemy::OnCollisionExit(CollisionObject* pOther)
{
	// TODO: make a debug flag for this
	std::cout << "Enemy has exited collision" << std::endl;
}
