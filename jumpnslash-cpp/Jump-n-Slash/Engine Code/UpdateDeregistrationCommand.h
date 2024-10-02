#ifndef UPDATE_DEREGISTRATION_COMMAND_H
#define UPDATE_DEREGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class UpdateObject;

class UpdateDeregistrationCommand : public Command
{
public:
	UpdateDeregistrationCommand() = delete;
	UpdateDeregistrationCommand(UpdateObject* pUpdatable);
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand& udc);
	UpdateDeregistrationCommand& operator=(const UpdateDeregistrationCommand& udc);
	virtual ~UpdateDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	UpdateObject* pUpdatable;
};

#endif