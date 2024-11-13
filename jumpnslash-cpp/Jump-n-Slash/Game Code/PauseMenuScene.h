#ifndef PAUSE_MENU_SCENE_H
#define PAUSE_MENU_SCENE_H

// engine includes
#include "../Engine Code/MenuScene.h"

// forward declarations
class PauseMenu;

class PauseMenuScene : public MenuScene
{
public:
	PauseMenuScene();
	PauseMenuScene(const PauseMenuScene& pms) = delete;
	PauseMenuScene& operator=(const PauseMenuScene& pms) = delete;
	virtual ~PauseMenuScene();

	virtual void Init() override;
	virtual void End() override;

private:
	PauseMenu* pPauseMenu;
};

#endif