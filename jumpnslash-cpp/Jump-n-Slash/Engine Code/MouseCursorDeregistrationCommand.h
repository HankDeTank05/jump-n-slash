#ifndef MOUSE_CURSOR_DEREGISTRATION_COMMAND_H
#define MOUSE_CURSOR_DEREGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class InputObject;

class MouseCursorDeregistrationCommand : public Command
{
public:
	MouseCursorDeregistrationCommand() = delete;
	MouseCursorDeregistrationCommand(InputObject* pInputable);
	MouseCursorDeregistrationCommand(const MouseCursorDeregistrationCommand& mcdc);
	MouseCursorDeregistrationCommand& operator=(const MouseCursorDeregistrationCommand& mcdc);
	virtual ~MouseCursorDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
};

#endif