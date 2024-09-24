#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "../Engine Code/Scene.h"

// forward declarations
class Player;

class TestScene : public Scene
{
public:
	TestScene();
	TestScene(const TestScene& ts) = delete;
	TestScene& operator=(const TestScene& ts) = delete;
	virtual ~TestScene();

	virtual void Init() override;
	virtual void End() override;

private:
	Player* pPlayer;
};

#endif