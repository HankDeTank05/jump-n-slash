#include "AnimationComponent.h"

#include "AnimationSet.h"
#include "TimeManager.h"

AnimationComponent::AnimationComponent()
	: pAnimSet(new AnimationSet()),
	pCurrentAnim(nullptr),
	currentFrameIt(),
	animTimer(0.f)
{
	// do nothing
}

AnimationComponent::~AnimationComponent()
{
	delete pAnimSet;
}

void AnimationComponent::DefineAnimation(const std::string& animName, Animation* pAnim)
{
	pAnimSet->AddAnimation(animName, pAnim);
}

void AnimationComponent::SetAnimation(const std::string& animName)
{
	pCurrentAnim = pAnimSet->GetAnimation(animName);
	currentFrameIt = pCurrentAnim->GetFirstFrame();
	animTimer = 0.f;
}

Sprite* AnimationComponent::GetCurrentFrame()
{
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
