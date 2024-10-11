#ifndef SCENE_CHANGE_COMMAND_H
#define SCENE_CHANGE_COMMAND_H

#include "SceneCommand.h"

// forward declarations
class Scene;

class SceneChangeCommand : public SceneCommand
{
public:
	SceneChangeCommand() = default;
	SceneChangeCommand(const SceneChangeCommand& scc) = delete;
	SceneChangeCommand& operator=(const SceneChangeCommand& scc) = delete;
	virtual ~SceneChangeCommand() = default;

	virtual void Execute() override;
};

#endif