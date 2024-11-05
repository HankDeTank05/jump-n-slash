#ifndef MENU_COMMAND_H
#define MENU_COMMAND_H

// engine includes
#include "../Engine Code/Command.h"

class MenuCommand : public Command
{
public:
	MenuCommand() = default;
	MenuCommand(const MenuCommand& mc) = delete;
	MenuCommand& operator=(const MenuCommand& mc) = delete;
	virtual ~MenuCommand() = default;

	virtual void Execute() = 0;
};

#endif