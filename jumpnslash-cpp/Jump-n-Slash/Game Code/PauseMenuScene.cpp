#include "PauseMenuScene.h"

// game includes
#include "PauseMenu.h"

PauseMenuScene::PauseMenuScene()
	: pPauseMenu(new PauseMenu(GetMenuManager()))
{
}

PauseMenuScene::~PauseMenuScene()
{
	delete pPauseMenu;
}

void PauseMenuScene::Init()
{
	SetStartingMenu(pPauseMenu);
}

void PauseMenuScene::End()
{
	// do nothing
}
