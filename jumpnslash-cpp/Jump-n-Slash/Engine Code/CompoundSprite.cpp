#include "CompoundSprite.h"

// engine includes
#include "AnimationComponent.h"

void CompoundSprite::AddSubsprite(const std::string& subsprName, const std::string& reqdConnName)
{
	sprites.emplace(subsprName, nullptr);
	animComps.emplace(subsprName, new AnimationComponent());
	connsRequired.emplace(subsprName, std::list<std::string>());

	AddRequiredConnector(subsprName, reqdConnName);
}

void CompoundSprite::AddRequiredConnector(const std::string& subsprName, const std::string& connName)
{
	assert(connsRequired.count(subsprName) > 0); // no subsprite found with the given name!

	for (std::list<std::string>::iterator it = connsRequired.at(subsprName).begin(); it != connsRequired.at(subsprName).end(); it++)
	{
		assert((*it) != connName); // no duplicate connection names!
	}

	connsRequired.at(subsprName).push_back(connName);
}

void CompoundSprite::DefineAnimation(const std::string& subsprName, const std::string& animName, Animation* pAnim)
{
	assert(animComps.count(subsprName) > 0); // no subsprite found withthe given name

	//animComps.at(subsprName)->DefineAnimation(animName, pAnim);
}

std::map<std::string, Sprite*> CompoundSprite::GetCurrentFrames()
{
	for (std::map<std::string, Sprite*>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		std::string subsprName = it->first;
		it->second = animComps.at(subsprName)->GetCurrentFrame();
	}

	return sprites;
}
