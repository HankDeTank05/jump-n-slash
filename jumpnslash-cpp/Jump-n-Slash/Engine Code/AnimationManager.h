#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <list>
#include <map>

// forward declarations
class Animation;

class AnimationManager // this class is written as a singleton
{
private:
	static AnimationManager* pInstance;

	AnimationManager() = default;
	AnimationManager(const AnimationManager& am) = delete;
	AnimationManager& operator=(const AnimationManager& am) = delete;
	virtual ~AnimationManager();

	static AnimationManager& Instance();

public: // api functions
	static void LoadAnimation(std::string key, std::list<std::string> spriteKeyList, float fps, bool loop); // TODO: docs for AnimationManager::LoadAnimation
	static Animation* GetAnimation(std::string key); // TODO: docs for AnimationManager::GetAnimation

private: // engine-only api functions
	static void Terminate();

private: // api backend functions
	void privLoadAnimation(std::string key, std::list<std::string> spriteKeyList, float fps, bool loop);
	Animation* privGetAnimation(std::string key);

private: // member variables
	std::map<std::string, Animation*> animations;
};

#endif