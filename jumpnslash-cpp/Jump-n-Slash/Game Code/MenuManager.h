#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

// language includes
#include <stack>

// forward declarations
class Menu;

class MenuManager
{
public:
	MenuManager();
	MenuManager(const MenuManager& mm) = delete;
	MenuManager& operator=(const MenuManager& mm) = delete;
	virtual ~MenuManager();

	void SetStartingMenu(Menu* pStartingMenu);
	void EnterSubmenu(Menu* pSubmenu);
	void ReturnToPrevMenu();

private: // member variables
	Menu* pStartingMenu;
	Menu* pCurrentMenu;
	std::stack<Menu*> menuStack;
};

#endif