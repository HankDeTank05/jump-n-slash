#ifndef UPDATE_REGISTRATION_COMMAND_H
#define UPDATE_REGISTRATION_COMMAND_H

#include "Command.h"

// forward declarations
class UpdatableObject;

class UpdateRegistrationCommand : public Command
{
public:
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(UpdatableObject* pUpdatable);
	UpdateRegistrationCommand(const UpdateRegistrationCommand& urc);
	UpdateRegistrationCommand& operator=(const UpdateRegistrationCommand& urc);
	virtual ~UpdateRegistrationCommand() = default;

	virtual void Execute() override;

private:
	UpdatableObject* pUpdatable;
};

#endif