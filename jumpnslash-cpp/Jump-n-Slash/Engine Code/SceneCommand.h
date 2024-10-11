#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include "Command.h"

// forward declarations
class Scene;

class SceneCommand : public Command
{
public:
	SceneCommand();
	SceneCommand(const SceneCommand& sc) = delete;
	SceneCommand& operator=(const SceneCommand& sc) = delete;
	virtual ~SceneCommand() = default;

	virtual void Execute() = 0;

	void SetNextScene(Scene* pNextScene);

protected:
	Scene* pNextScene;
};

#endif