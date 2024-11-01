#include "GamepadBtnRegistrationCommand.h"

#include "InputObjectAttorney.h"

GamepadBtnRegistrationCommand::GamepadBtnRegistrationCommand(InputObject* _pInputable, int _gamepadIndex, int _btnNum, GamepadBtnEvent _eventToReg)
	: pInputable(_pInputable),
	gamepadIndex(_gamepadIndex),
	btnNum(_btnNum),
	eventToReg(_eventToReg)
{
	// do nothing
}

void GamepadBtnRegistrationCommand::Execute()
{
	InputObjectAttorney::Registration::RegisterGamepadBtn(pInputable, gamepadIndex, btnNum, eventToReg);
}
