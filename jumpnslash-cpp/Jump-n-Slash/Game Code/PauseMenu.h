#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Menu.h"

class PauseMenu : public Menu
{
public:
	PauseMenu() = delete;
	PauseMenu(MenuManager* pMgr);
	PauseMenu(const PauseMenu& pm) = delete;
	PauseMenu& operator=(const PauseMenu& pm) = delete;
	virtual ~PauseMenu() = default;
};

#endif