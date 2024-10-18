#include "AnimationManager.h"

#include "SpriteManager.h"
#include "Animation.h"

AnimationManager* AnimationManager::pInstance = nullptr;

AnimationManager::~AnimationManager()
{
	for (std::map<std::string, Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
	{
		delete it->second;
	}
}

AnimationManager& AnimationManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new AnimationManager();
	}
	return *pInstance;
}

void AnimationManager::LoadAnimation(std::string key, std::list<std::string> spriteKeyList, float fps, bool loop)
{
	Instance().privLoadAnimation(key, spriteKeyList, fps, loop);
}

Animation* AnimationManager::GetAnimation(std::string key)
{
	return Instance().privGetAnimation(key);
}

void AnimationManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void AnimationManager::privLoadAnimation(std::string key, std::list<std::string> spriteKeyList, float fps, bool loop)
{
	assert(animations.count(key) == 0); // no duplicate keys allowed!

	Animation* pAnim = new Animation(fps, loop);
	for (std::list<std::string>::iterator it = spriteKeyList.begin(); it != spriteKeyList.end(); it++)
	{
		pAnim->AddFrame(SpriteManager::GetSprite(*it));
	}

	animations.emplace(key, pAnim);
}

Animation* AnimationManager::privGetAnimation(std::string key)
{
	assert(animations.count(key) > 0); // key not found in map!

	return animations.at(key);
}
