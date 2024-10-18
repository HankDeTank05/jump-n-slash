#include "AnimationComponent.h"

#include "AnimationSet.h"
#include "TimeManager.h"

AnimationComponent::AnimationComponent()
	: pAnimSet(nullptr),
	pCurrentAnim(nullptr),
	currentFrameIt(),
	animTimer(0.f)
{
	// do nothing
}

AnimationComponent::~AnimationComponent()
{
	if (pAnimSet != nullptr)
	{
		delete pAnimSet;
	}
}

void AnimationComponent::DefineAnimationSet(AnimationSet* _pAnimSet)
{
	assert(pAnimSet == nullptr); // can only define the animationset once

	pAnimSet = _pAnimSet;
}

void AnimationComponent::SetAnimation(std::string animName)
{
	assert(pAnimSet != nullptr);

	pCurrentAnim = pAnimSet->GetAnimation(animName);
	currentFrameIt = pCurrentAnim->GetFirstFrame();
	animTimer = 0.f;
}

sf::Sprite* AnimationComponent::GetCurrentFrame()
{
	assert(pAnimSet != nullptr);

	animTimer += TimeManager::GetFrameTime();
	if (pCurrentAnim->IsLooping() == true ||
		(pCurrentAnim->IsLooping() == false && pCurrentAnim->IsLastFrame(currentFrameIt) == false))
	{
		while (animTimer >= pCurrentAnim->GetSPF())
		{
			animTimer -= pCurrentAnim->GetSPF();
			currentFrameIt = pCurrentAnim->GetNextFrame(currentFrameIt);
		}
	}

	return (*currentFrameIt);
}
