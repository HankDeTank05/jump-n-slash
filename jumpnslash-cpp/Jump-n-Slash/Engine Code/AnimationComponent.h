#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.h"

// forward declarations
class AnimationSet;

class AnimationComponent
{
public:
	AnimationComponent();
	AnimationComponent(const AnimationComponent& ao) = delete;
	AnimationComponent& operator=(const AnimationComponent& ao) = delete;
	virtual ~AnimationComponent();

	void DefineAnimationSet(AnimationSet* pAnimSet); // TODO: docs for AnimationComponent::DefineAnimationSet

	void SetAnimation(std::string animName); // TODO: docs for AnimationComponent::SetAnimation
	sf::Sprite* GetCurrentFrame(); // TODO: docs for AnimationComponent::GetCurrentFrame

private:
	AnimationSet* pAnimSet;
	Animation* pCurrentAnim;
	Animation::Iterator currentFrameIt;
	float animTimer;
};

#endif