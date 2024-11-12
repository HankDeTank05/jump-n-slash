#ifndef CHANGE_CONTROL_COMMAND_H
#define CHANGE_CONTROLS_COMMAND_H

// game includes
#include "EnterSubmenuCommand.h"

// forward declarations
class MenuManager;

class ChangeControlsCommand : public EnterSubmenuCommand
{
public:
	ChangeControlsCommand() = delete;
	ChangeControlsCommand(MenuManager* pMgr);
	ChangeControlsCommand(const ChangeControlsCommand& ccc) = delete;
	ChangeControlsCommand& operator=(const ChangeControlsCommand& ccc) = delete;
	virtual ~ChangeControlsCommand() = default;

	//virtual void Execute() override;
};

#endif