#include "MenuManager.h"

// engine includes
#include "MenuAttorney.h"

MenuManager::MenuManager()
	: pStartingMenu(nullptr),
	pCurrentMenu(nullptr),
	menuStack()
{
	// do nothing
}

void MenuManager::SetStartingMenu(Menu* _pStartingMenu)
{
	pStartingMenu = _pStartingMenu;
	pCurrentMenu = pStartingMenu;
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}

void MenuManager::EnterSubmenu(Menu* pSubmenu)
{
	// end the current menu
	assert(pCurrentMenu != nullptr);
	MenuAttorney::MenuManagerAccess::End(pCurrentMenu);

	// push the current menu to the stack to be restored later
	menuStack.push(pCurrentMenu);

	// set and init the new current menu
	pCurrentMenu = pSubmenu;
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}

void MenuManager::ReturnToPrevMenu()
{
	// end the current menu
	MenuAttorney::MenuManagerAccess::End(pCurrentMenu);

	// restore the most recent menu
	assert(menuStack.size() > 0);
	pCurrentMenu = menuStack.top();
	menuStack.pop();

	// init the new current menu
	MenuAttorney::MenuManagerAccess::Init(pCurrentMenu);
}
