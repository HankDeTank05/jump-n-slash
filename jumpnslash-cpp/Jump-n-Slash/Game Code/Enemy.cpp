#include "Enemy.h"

#include "Constants.h"

#include "../Engine Code/AnimationSet.h"
#include "../Engine Code/AnimationManager.h"

Enemy::Enemy()
	: pos(30 * TILE_SIZE_F, 19* TILE_SIZE_F),
	posDelta(0.f, 0.f),
	pSprite(nullptr),
	animComp()
{
	AnimationSet* pAnimSet = new AnimationSet();

	pAnimSet->AddAnimation("idle", AnimationManager::GetAnimation("enemy idle"));

	animComp.DefineAnimationSet(pAnimSet);
	animComp.SetAnimation("idle");
}

Enemy::~Enemy()
{
	// do nothing
}

void Enemy::Update(float deltaTime)
{
	pSprite = animComp.GetCurrentFrame();
	pSprite->setPosition(pos);
}

void Enemy::Draw()
{
	assert(pSprite != nullptr);
	Render(*pSprite);
}
