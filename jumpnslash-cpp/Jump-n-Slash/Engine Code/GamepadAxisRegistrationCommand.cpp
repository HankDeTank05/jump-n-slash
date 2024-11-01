#include "GamepadAxisRegistrationCommand.h"

#include "InputObjectAttorney.h"

GamepadAxisRegistrationCommand::GamepadAxisRegistrationCommand(InputObject* _pInputable, int _gamepadIndex, sf::Joystick::Axis _axis, GamepadAxisEvent _eventToReg)
	: pInputable(_pInputable),
	gamepadIndex(_gamepadIndex),
	axis(_axis),
	eventToReg(_eventToReg)
{
	// do nothing
}

void GamepadAxisRegistrationCommand::Execute()
{
	InputObjectAttorney::Registration::RegisterGamepadAxis(pInputable, gamepadIndex, axis, eventToReg);
}
