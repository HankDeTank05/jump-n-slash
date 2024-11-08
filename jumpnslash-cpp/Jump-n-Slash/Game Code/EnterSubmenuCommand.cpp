#include "EnterSubmenuCommand.h"

// game includes
#include "MenuManager.h"

EnterSubmenuCommand::EnterSubmenuCommand(MenuManager* _pMgr, Menu* _pSubmenu)
	: pMgr(_pMgr),
	pSubmenu(_pSubmenu)
{
	assert(pMgr != nullptr);
	assert(pSubmenu != nullptr);
}

EnterSubmenuCommand::~EnterSubmenuCommand()
{
	delete pSubmenu;
}

void EnterSubmenuCommand::Execute()
{
	pMgr->EnterSubmenu(pSubmenu);
}
