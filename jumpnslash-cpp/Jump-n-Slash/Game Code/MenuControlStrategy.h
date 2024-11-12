#ifndef MENU_CONTROL_STRATEGY_H
#define MENU_CONTROL_STRATEGY_H

#include "../Engine Code/InputObject.h"
#include "../Engine Code/ControlScheme.h"

// forward declarations
class Menu;

class MenuControlStrategy : public InputObject
{
public:
	MenuControlStrategy() = delete;
	MenuControlStrategy(Menu* pMenu, ControlScheme ctrl);
	MenuControlStrategy(const MenuControlStrategy& mcs) = delete;
	MenuControlStrategy& operator=(const MenuControlStrategy& mcs) = delete;
	virtual ~MenuControlStrategy() = default;

protected:
	Menu* pMenu;
	bool navUp;
	bool navDown;
	bool select;
}

#endif