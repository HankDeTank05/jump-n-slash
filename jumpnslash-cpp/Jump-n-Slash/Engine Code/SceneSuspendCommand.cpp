#include "SceneSuspendCommand.h"

#include "SceneManagerAttorney.h"

void SceneSuspendCommand::Execute()
{
	SceneManagerAttorney::SceneSuspend::SuspendCurrentScene(pNextScene);
}
