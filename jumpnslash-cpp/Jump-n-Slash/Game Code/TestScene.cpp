#include "TestScene.h"

#include "TestClass.h"

TestScene::TestScene()
	: pTestClass(nullptr)
{
	// do nothing
}

TestScene::~TestScene()
{
	// do nothing
}

void TestScene::Init()
{
	pTestClass = new TestClass();
}

void TestScene::End()
{
	delete pTestClass;
}
