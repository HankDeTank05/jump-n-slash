#ifndef DRAW_DEREGISTRATION_COMMAND_H
#define DRAW_DEREGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class DrawableObject;

class DrawDeregistrationCommand : public Command
{
public:
	DrawDeregistrationCommand() = delete;
	DrawDeregistrationCommand(DrawableObject* pDrawable);
	DrawDeregistrationCommand(const DrawDeregistrationCommand& ddc);
	DrawDeregistrationCommand& operator=(const DrawDeregistrationCommand& ddc);
	virtual ~DrawDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	DrawableObject* pDrawable;
};

#endif