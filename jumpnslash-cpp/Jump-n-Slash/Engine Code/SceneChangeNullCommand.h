#ifndef SCENE_CHANGE_NULL_COMMAND_H
#define SCENE_CHANGE_NULL_COMMAND_H

#include "SceneCommand.h"

class SceneChangeNullCommand : public SceneCommand
{
public:
	SceneChangeNullCommand() = default;
	SceneChangeNullCommand(const SceneChangeNullCommand& scnc) = delete;
	SceneChangeNullCommand& operator=(const SceneChangeNullCommand& scnc) = delete;
	virtual ~SceneChangeNullCommand() = default;

	virtual void Execute() override;
};

#endif