#include "MenuManager.h"

MenuManager::MenuManager()
	: pStartingMenu(nullptr),
	pCurrentMenu(nullptr),
	menuStack()
{
	// do nothing
}

MenuManager::~MenuManager()
{
	delete pStartingMenu;
}

void MenuManager::SetStartingMenu(Menu* _pStartingMenu)
{
	pStartingMenu = _pStartingMenu;
	pCurrentMenu = pStartingMenu;
}

void MenuManager::EnterSubmenu(Menu* pSubmenu)
{
	assert(pCurrentMenu != nullptr);
	menuStack.push(pCurrentMenu);
	pCurrentMenu = pSubmenu;
}

void MenuManager::ReturnToPrevMenu()
{
	assert(menuStack.size() > 0);
	pCurrentMenu = menuStack.top();
	menuStack.pop();
}
