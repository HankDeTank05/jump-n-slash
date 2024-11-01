#ifndef GAMEPAD_AXIS_REGISTRATION_COMMAND_H
#define GAMEPAD_AXIS_REGISTRATION_COMMAND_H

#include <SFML/Window/Joystick.hpp>

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadAxisRegistrationCommand : public Command
{
public:
	GamepadAxisRegistrationCommand() = delete;
	GamepadAxisRegistrationCommand(InputObject* pInputable, int gamepadIndex, sf::Joystick::Axis axis, GamepadAxisEvent eventToReg);
	GamepadAxisRegistrationCommand(const GamepadAxisRegistrationCommand& garc) = delete;
	GamepadAxisRegistrationCommand& operator=(const GamepadAxisRegistrationCommand& garc) = delete;
	virtual ~GamepadAxisRegistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	int gamepadIndex;
	sf::Joystick::Axis axis;
	GamepadAxisEvent eventToReg;
};

#endif