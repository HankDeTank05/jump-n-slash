#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

// engine includes
#include "Animation.h"

// forward declarations
class AnimationSet;
class Sprite;

class AnimationComponent
{
public:
	AnimationComponent();
	AnimationComponent(const AnimationComponent& ao) = delete;
	AnimationComponent& operator=(const AnimationComponent& ao) = delete;
	virtual ~AnimationComponent();

	void DefineAnimation(const std::string& animName, Animation* pAnim); // TODO: docs for AnimationComponent::DefineAnimation

	void SetAnimation(const std::string& animName); // TODO: docs for AnimationComponent::SetAnimation
	Sprite* GetCurrentFrame(); // TODO: docs for AnimationComponent::GetCurrentFrame

private:
	AnimationSet* pAnimSet;
	Animation* pCurrentAnim;
	Animation::Iterator currentFrameIt;
	float animTimer;
};

#endif