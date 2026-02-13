#ifndef CHANGE_CONTROLS_MENU_H
#define CHANGE_CONTROLS_MENU_H

// engine includes
#include "../Engine Code/Menu.h"

// forward declarations
class MenuManager;

class ChangeControlsMenu : public Menu
{
public:
	ChangeControlsMenu() = delete;
	ChangeControlsMenu(MenuManager* pMgr);
	ChangeControlsMenu(const ChangeControlsMenu& ccm) = delete;
	ChangeControlsMenu& operator=(const ChangeControlsMenu& ccm) = delete;
	virtual ~ChangeControlsMenu() = default;
};

#endif