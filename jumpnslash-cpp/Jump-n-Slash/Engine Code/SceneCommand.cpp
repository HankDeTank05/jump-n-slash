#include "SceneCommand.h"

SceneCommand::SceneCommand()
	: pNextScene(nullptr)
{
	// do nothing
}

void SceneCommand::SetNextScene(Scene* _pNextScene)
{
	pNextScene = _pNextScene;
}
