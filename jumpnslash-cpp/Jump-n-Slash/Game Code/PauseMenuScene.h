#ifndef PAUSE_MENU_SCENE_H
#define PAUSE_MENU_SCENE_H

// game includes
#include "MenuScene.h"

class PauseMenuScene : public MenuScene
{
public:
	PauseMenuScene() = default;
	PauseMenuScene(const PauseMenuScene& pms) = delete;
	PauseMenuScene& operator=(const PauseMenuScene& pms) = delete;
	virtual ~PauseMenuScene() = default;

	virtual void Init() override;
	virtual void End() override;
};

#endif