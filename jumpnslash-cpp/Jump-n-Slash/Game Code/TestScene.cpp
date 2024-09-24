#include "TestScene.h"

#include "Player.h"

TestScene::TestScene()
	: pPlayer(nullptr)
{
	// do nothing
}

TestScene::~TestScene()
{
	// do nothing
}

void TestScene::Init()
{
	pPlayer = new Player();
}

void TestScene::End()
{
	delete pPlayer;
}
