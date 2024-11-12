#include "ChangeControlsCommand.h"

// game includes
#include "ChangeControlsMenu.h"

ChangeControlsCommand::ChangeControlsCommand(MenuManager* pMgr)
	: EnterSubmenuCommand(pMgr, new ChangeControlsMenu(pMgr))
{
	// do nothing
}
