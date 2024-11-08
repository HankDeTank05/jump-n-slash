#include "ExitSubmenuCommand.h"

// game includes
#include "MenuManager.h"

ExitSubmenuCommand::ExitSubmenuCommand(MenuManager* _pMgr)
	: pMgr(_pMgr)
{
	assert(pMgr != nullptr);
}

void ExitSubmenuCommand::Execute()
{
	pMgr->ReturnToPrevMenu();
}
