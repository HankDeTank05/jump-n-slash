#ifndef MOUSE_BTN_REGISTRATION_COMMAND_H
#define MOUSE_BTN_REGISTRATION_COMMAND_H

#include <SFML/Window/Mouse.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class MouseBtnRegistrationCommand : public Command
{
public:
	MouseBtnRegistrationCommand() = delete;
	MouseBtnRegistrationCommand(InputObject* pInputable, sf::Mouse::Button btn, KeyEvent eventToDereg);
	MouseBtnRegistrationCommand(const MouseBtnRegistrationCommand& mbrc);
	MouseBtnRegistrationCommand& operator=(const MouseBtnRegistrationCommand& mbrc);
	virtual ~MouseBtnRegistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	sf::Mouse::Button btn;
	KeyEvent eventToDereg;
};

#endif