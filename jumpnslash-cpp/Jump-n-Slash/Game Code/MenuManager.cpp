#include "MenuManager.h"

#include "MenuAttorney.h"

MenuManager::MenuManager()
	: pStartingMenu(nullptr),
	pCurrentMenu(nullptr),
	menuStack()
{
	// do nothing
}

MenuManager::~MenuManager()
{
	//delete pStartingMenu;
}

void MenuManager::SetStartingMenu(Menu* _pStartingMenu)
{
	pStartingMenu = _pStartingMenu;
	pCurrentMenu = pStartingMenu;
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}

void MenuManager::EnterSubmenu(Menu* pSubmenu)
{
	assert(pCurrentMenu != nullptr);
	MenuAttorney::MenuManagerAccess::End(pCurrentMenu);
	menuStack.push(pCurrentMenu);
	pCurrentMenu = pSubmenu;
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}

void MenuManager::ReturnToPrevMenu()
{
	assert(menuStack.size() > 0);
	MenuAttorney::MenuManagerAccess::End(pCurrentMenu);
	// TODO: mem leak here. either delete or make a factory/object pool
	pCurrentMenu = menuStack.top();
	menuStack.pop();
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}
