#include "SceneResumeCommand.h"

#include "SceneManagerAttorney.h"

void SceneResumeCommand::Execute()
{
	SceneManagerAttorney::SceneResume::ResumeSuspendedScene();
}
