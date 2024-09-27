#ifndef MOUSE_CURSOR_REGISTRATION_COMMAND_H
#define MOUSE_CURSOR_REGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class InputObject;

class MouseCursorRegistrationCommand : public Command
{
public:
	MouseCursorRegistrationCommand() = delete;
	MouseCursorRegistrationCommand(InputObject* pInputable);
	MouseCursorRegistrationCommand(const MouseCursorRegistrationCommand& mcrc);
	MouseCursorRegistrationCommand& operator=(const MouseCursorRegistrationCommand& mcrc);
	virtual ~MouseCursorRegistrationCommand() = default;

	virtual void Execute() override;

private:
	InputObject* pInputable;
};

#endif