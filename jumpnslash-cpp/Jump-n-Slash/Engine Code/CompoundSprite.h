#ifndef COMPOUND_SPRITE_H
#define COMPOUND_SPRITE_H

// language includes
#include <string>
#include <map>
#include <list>

// forward declarations
class Sprite;
class AnimationComponent;
class AnimationSet;

class CompoundSprite
{
public:
	CompoundSprite() = default;
	CompoundSprite(const CompoundSprite& cs) = delete;
	CompoundSprite& operator=(const CompoundSprite& cs) = delete;
	virtual ~CompoundSprite() = default;

	void AddSubsprite(const std::string& subsprName, const std::string& reqdConnName);
	void AddRequiredConnector(const std::string& subsprName, const std::string& connName);

	void DefineAnimationSet(const std::string& subsprName, const std::string& animName, Animation* pAnim);

private:
	std::map<std::string, Sprite*> sprites;
	std::map<std::string, AnimationComponent*> animComps;
	std::map<std::string, std::list<std::string>> connsRequired;
};

#endif