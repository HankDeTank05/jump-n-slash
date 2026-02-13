#include "MenuScene.h"

// engine includes
#include "MenuManager.h"

MenuScene::MenuScene()
	: pMenuMgr(new MenuManager())
{
	// do nothing
}

MenuScene::~MenuScene()
{
	delete pMenuMgr;
}

MenuManager* MenuScene::GetMenuManager()
{
	return pMenuMgr;
}

void MenuScene::SetStartingMenu(Menu* pStartingMenu)
{
	pMenuMgr->SetStartingMenu(pStartingMenu);
}
