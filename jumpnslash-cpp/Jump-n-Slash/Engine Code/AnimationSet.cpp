#include "AnimationSet.h"

#include "Animation.h"

AnimationSet::~AnimationSet()
{
	animations.clear();
}

void AnimationSet::AddAnimation(std::string animName, Animation* pAnim)
{
	assert(animations.count(animName) == 0); // no duplicate animation names!

	animations.emplace(animName, pAnim);
}

Animation* AnimationSet::GetAnimation(std::string animName)
{
	assert(animations.count(animName) > 0);

	return animations.at(animName);
}
