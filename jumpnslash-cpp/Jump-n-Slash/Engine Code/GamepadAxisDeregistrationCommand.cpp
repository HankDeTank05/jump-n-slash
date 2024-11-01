#include "GamepadAxisDeregistrationCommand.h"

#include "InputObjectAttorney.h"

GamepadAxisDeregistrationCommand::GamepadAxisDeregistrationCommand(InputObject* _pInputable, int _gamepadIndex, sf::Joystick::Axis _axis, GamepadAxisEvent _eventToDereg)
	: pInputable(_pInputable),
	gamepadIndex(_gamepadIndex),
	axis(_axis),
	eventToDereg(_eventToDereg)
{
	// do nothing
}

void GamepadAxisDeregistrationCommand::Execute()
{
	InputObjectAttorney::Registration::DeregisterGamepadAxis(pInputable, gamepadIndex, axis, eventToDereg);
}
