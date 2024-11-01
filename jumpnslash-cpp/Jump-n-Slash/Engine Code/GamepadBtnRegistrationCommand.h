#ifndef GAMEPAD_BTN_REGISTRATION_COMMAND_H
#define GAMEPAD_BTN_REGISTRATION_COMMAND_H

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadBtnRegistrationCommand : public Command
{
public:
	GamepadBtnRegistrationCommand() = delete;
	GamepadBtnRegistrationCommand(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent gpBtnEvent);
	GamepadBtnRegistrationCommand(const GamepadBtnRegistrationCommand& gbrc) = delete;
	GamepadBtnRegistrationCommand& operator=(const GamepadBtnRegistrationCommand& gbrc) = delete;
	virtual ~GamepadBtnRegistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	int gamepadIndex;
	int btnNum;
	GamepadBtnEvent eventToReg;
};

#endif