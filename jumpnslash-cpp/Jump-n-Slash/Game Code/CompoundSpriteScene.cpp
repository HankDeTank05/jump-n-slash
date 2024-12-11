#include "CompoundSpriteScene.h"

// game includes
#include "CompSprTest.h"

CompoundSpriteScene::CompoundSpriteScene()
	: pGameObject(nullptr)
{
	// do nothing
}

CompoundSpriteScene::~CompoundSpriteScene()
{
	if (pGameObject != nullptr)
	{
		delete pGameObject;
	}
}

void CompoundSpriteScene::Init()
{
	pGameObject = new CompSprTest();
}

void CompoundSpriteScene::End()
{
	delete pGameObject;
	pGameObject = nullptr;
}
