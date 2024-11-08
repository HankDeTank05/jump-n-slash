#ifndef EXIT_SUBMENU_COMMAND_H
#define EXIT_SUBMENU_COMMAND_H

#include "MenuCommand.h"

// forward declarations
class MenuManager;

class ExitSubmenuCommand : public MenuCommand
{
public:
	ExitSubmenuCommand() = delete;
	ExitSubmenuCommand(MenuManager* pMgr);
	ExitSubmenuCommand(const ExitSubmenuCommand& esc) = delete;
	ExitSubmenuCommand& operator=(const ExitSubmenuCommand& esc) = delete;
	virtual ~ExitSubmenuCommand() = default;

	virtual void Execute() override;

protected:
	MenuManager* pMgr;
};

#endif