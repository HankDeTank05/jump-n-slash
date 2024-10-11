#include "SceneChangeCommand.h"

#include "SceneManagerAttorney.h"

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::SceneChange::ChangeScene(pNextScene);
}
