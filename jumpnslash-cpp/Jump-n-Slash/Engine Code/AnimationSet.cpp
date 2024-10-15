#include "AnimationSet.h"

AnimationSet::~AnimationSet()
{
	for (std::map<std::string, Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
	{
		delete (it->second);
	}
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
