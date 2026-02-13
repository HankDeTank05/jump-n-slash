#ifndef COMPOUND_SPRITE_SCENE_H
#define COMPOUND_SPRITE_SCENE_H

// engine includes
#include "../Engine Code/Scene.h"

// forward declarations
class CompSprTest;

class CompoundSpriteScene : public Scene
{
public:
	CompoundSpriteScene();
	CompoundSpriteScene(const CompoundSpriteScene& css) = delete;
	CompoundSpriteScene& operator=(const CompoundSpriteScene& css) = delete;
	virtual ~CompoundSpriteScene();

	virtual void Init() override;
	virtual void End() override;

private:
	CompSprTest* pGameObject;
};

#endif