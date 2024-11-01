#ifndef GAMEPAD_BTN_DEREGISTRATION_COMMAND_H
#define GAMEPAD_BTN_DEREGISTRATION_COMMAND_H

#include "Command.h"
#include "InputEvent.h"

// forward declarations
class InputObject;

class GamepadBtnDeregistrationCommand : public Command
{
public:
	GamepadBtnDeregistrationCommand() = delete;
	GamepadBtnDeregistrationCommand(InputObject* pInputable, int gamepadIndex, int btnNum, GamepadBtnEvent eventToDereg);
	GamepadBtnDeregistrationCommand(const GamepadBtnDeregistrationCommand& gbdc) = delete;
	GamepadBtnDeregistrationCommand& operator=(const GamepadBtnDeregistrationCommand& gbdc) = delete;
	virtual ~GamepadBtnDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
	int gamepadIndex;
	int btnNum;
	GamepadBtnEvent eventToDereg;
};

#endif