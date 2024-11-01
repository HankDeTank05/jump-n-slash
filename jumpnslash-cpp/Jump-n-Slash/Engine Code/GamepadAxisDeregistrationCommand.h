#ifndef GAMEPAD_AXIS_DEREGISTRATION_COMMAND_H
#define GAMEPAD_AXIS_DEREGISTRATION_COMMAND_H

#include <SFML/Window/Joystick.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadAxisDeregistrationCommand : public Command
{
public:
	GamepadAxisDeregistrationCommand() = delete;
	GamepadAxisDeregistrationCommand(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToDereg);
	GamepadAxisDeregistrationCommand(const GamepadAxisDeregistrationCommand& gadc) = delete;
	GamepadAxisDeregistrationCommand& operator=(const GamepadAxisDeregistrationCommand& gadc) = delete;
	virtual ~GamepadAxisDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	int gamepadIndex;
	sf::Joystick::Axis axis;
	GamepadAxisEvent eventToDereg;
};

#endif