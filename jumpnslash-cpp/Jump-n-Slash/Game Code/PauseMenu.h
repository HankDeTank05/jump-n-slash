#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

// engine includes
#include "../Engine Code/Menu.h"

// forward declarations
class ChangeControlsMenu;

class PauseMenu : public Menu
{
public:
	PauseMenu() = delete;
	PauseMenu(MenuManager* pMgr);
	PauseMenu(const PauseMenu& pm) = delete;
	PauseMenu& operator=(const PauseMenu& pm) = delete;
	virtual ~PauseMenu();

private:
	ChangeControlsMenu* pChangeCtrlMenu; // PauseMenu class DOES OWN this pointer
};

#endif