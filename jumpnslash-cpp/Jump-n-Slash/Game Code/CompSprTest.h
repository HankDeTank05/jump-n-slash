#ifndef COMP_SPR_TEST_H
#define COMP_SPR_TEST_H

// language includes
#include <map>
#include <string>

// engine includes
#include "../Engine Code/GameObject.h"

// forward declarations
class Sprite;
class SpriteTreeNode;

class CompSprTest : public GameObject
{
public:
	CompSprTest();
	CompSprTest(const CompSprTest& cst) = delete;
	CompSprTest& operator=(const CompSprTest& cst) = delete;
	virtual ~CompSprTest();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void OnSceneEntry() override;
	virtual void OnSceneExit() override;

private:
	std::map<std::string, Sprite*> marioParts;
	SpriteTreeNode* pRoot;
};

#endif