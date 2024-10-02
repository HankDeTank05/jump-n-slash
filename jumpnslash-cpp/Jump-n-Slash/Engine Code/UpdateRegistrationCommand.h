#ifndef UPDATE_REGISTRATION_COMMAND_H
#define UPDATE_REGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class UpdateObject;

class UpdateRegistrationCommand : public Command
{
public:
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(UpdateObject* pUpdatable);
	UpdateRegistrationCommand(const UpdateRegistrationCommand& urc);
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand& urc);
	virtual ~UpdateRegistrationCommand() = default;

	virtual void Execute() override;

private:
	UpdateObject* pUpdatable;
};

#endif