#ifndef MOUSE_BTN_DEREGISTRATION_COMMAND_H
#define MOUSE_BTN_DEREGISTRATION_COMMAND_H

#include <SFML/Window/Mouse.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class MouseBtnDeregistrationCommand : public Command
{
public:
	MouseBtnDeregistrationCommand() = delete;
	MouseBtnDeregistrationCommand(InputObject* pInputable, sf::Mouse::Button btn, MouseEvent eventToDereg);
	MouseBtnDeregistrationCommand(const MouseBtnDeregistrationCommand& mbdc);
	MouseBtnDeregistrationCommand& operator=(const MouseBtnDeregistrationCommand& mbdc);
	virtual ~MouseBtnDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	sf::Mouse::Button btn;
	MouseEvent eventToDereg;
};

#endif