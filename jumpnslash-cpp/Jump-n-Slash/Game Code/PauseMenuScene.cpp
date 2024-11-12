#include "PauseMenuScene.h"

// game includes
#include "PauseMenu.h"

void PauseMenuScene::Init()
{
	SetStartingMenu(new PauseMenu(GetMenuManager()));
}

void PauseMenuScene::End()
{
	// do nothing
}
