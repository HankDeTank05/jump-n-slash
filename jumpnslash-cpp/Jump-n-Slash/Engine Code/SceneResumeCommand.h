#ifndef SCENE_RESUME_COMMAND_H
#define SCENE_RESUME_COMMAND_H

#include "SceneCommand.h"

class SceneResumeCommand : public SceneCommand
{
public:
	SceneResumeCommand() = default;
	SceneResumeCommand(const SceneResumeCommand& src) = delete;
	SceneResumeCommand& operator=(const SceneResumeCommand& src) = delete;
	virtual ~SceneResumeCommand() = default;

	virtual void Execute() override;
};

#endif