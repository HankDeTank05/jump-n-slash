#include "GamepadBtnDeregistrationCommand.h"

#include "InputObjectAttorney.h"

GamepadBtnDeregistrationCommand::GamepadBtnDeregistrationCommand(InputObject* _pInputable, int _gamepadIndex, int _btnNum, GamepadBtnEvent _eventToDereg)
	: pInputable(_pInputable),
	gamepadIndex(_gamepadIndex),
	btnNum(_btnNum),
	eventToDereg(_eventToDereg)
{
	// do nothing
}

void GamepadBtnDeregistrationCommand::Execute()
{
	InputObjectAttorney::Registration::DeregisterGamepadBtn(pInputable, gamepadIndex, btnNum, eventToDereg);
}
