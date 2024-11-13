#include "EnterSubmenuCommand.h"

// game includes
#include "MenuManager.h"
#include "Menu.h"

EnterSubmenuCommand::EnterSubmenuCommand(MenuManager* _pMgr, Menu* _pSubmenu)
	: pMgr(_pMgr),
	pSubmenu(_pSubmenu)
{
	assert(pMgr != nullptr);
	assert(pSubmenu != nullptr);
}

void EnterSubmenuCommand::Execute()
{
	pMgr->EnterSubmenu(pSubmenu);
}
