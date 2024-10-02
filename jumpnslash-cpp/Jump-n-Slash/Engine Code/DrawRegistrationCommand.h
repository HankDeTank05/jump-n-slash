#ifndef DRAW_REGISTRATION_COMMAND_H
#define DRAW_REGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class DrawObject;

class DrawRegistrationCommand : public Command
{
public:
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(DrawObject* pDrawObj);
	DrawRegistrationCommand(const DrawRegistrationCommand& drc);
	DrawRegistrationCommand& operator=(const DrawRegistrationCommand& drc);
	virtual ~DrawRegistrationCommand() = default;

	virtual void Execute() override;

private:
	DrawObject* pDrawable;
};

#endif