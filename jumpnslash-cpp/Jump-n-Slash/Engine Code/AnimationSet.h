#ifndef ANIMATION_SET_H
#define ANIMATION_SET_H

#include <map>

#include <SFML/Graphics/Sprite.hpp>

// forward declarations
class Animation;

class AnimationSet
{
public:
	AnimationSet() = default;
	AnimationSet(const AnimationSet& as) = delete;
	AnimationSet& operator=(const AnimationSet& as) = delete;
	virtual ~AnimationSet();

	void AddAnimation(std::string animName, Animation* pAnim); // TODO: docs for AnimationSet::AddAnimation
	Animation* GetAnimation(std::string animName); // TODO: docs for AnimationSet::GetAnimation

private:
	std::map<std::string, Animation*> animations;
};

#endif