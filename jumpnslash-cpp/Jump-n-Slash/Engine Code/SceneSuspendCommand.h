#ifndef SCENE_SUSPEND_COMMAND_H
#define SCENE_SUSPEND_COMMAND_H

#include "SceneCommand.h"

class SceneSuspendCommand : public SceneCommand
{
public:
	SceneSuspendCommand() = default;
	SceneSuspendCommand(const SceneSuspendCommand& ssc) = delete;
	SceneSuspendCommand& operator=(const SceneSuspendCommand& ssc) = delete;
	virtual ~SceneSuspendCommand() = default;

	virtual void Execute() override;
};

#endif