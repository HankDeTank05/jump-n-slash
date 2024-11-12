#ifndef ENTER_SUBMENU_COMMAND_H
#define ENTER_SUBMENU_COMMAND_H

// game includes
#include "MenuCommand.h"

// forward declarations
class MenuManager;
class Menu;

class EnterSubmenuCommand : public MenuCommand
{
public:
	EnterSubmenuCommand() = delete;
	EnterSubmenuCommand(MenuManager* pMgr, Menu* pSubmenu);
	EnterSubmenuCommand(const EnterSubmenuCommand& esc) = delete;
	EnterSubmenuCommand& operator=(const EnterSubmenuCommand& esc) = delete;
	virtual ~EnterSubmenuCommand();

	virtual void Execute() override final;

protected:
	MenuManager* pMgr;
	Menu* pSubmenu;
};

#endif