#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

class AnimationManager // this class is written as a singleton
{
private:
	static AnimationManager* pInstance;

	AnimationManager() = default;
	AnimationManager(const AnimationManager& am) = delete;
	AnimationManager& operator=(const AnimationManager& am) = delete;
	virtual ~AnimationManager();

	static AnimationManager& Instance();

public:
};

#endif