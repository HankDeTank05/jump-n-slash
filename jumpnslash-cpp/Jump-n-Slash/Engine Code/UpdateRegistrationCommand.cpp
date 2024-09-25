#include "UpdateRegistrationCommand.h"

#include "UpdatableObjectAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(UpdatableObject* _pUpdatable)
	: pUpdatable(_pUpdatable)
{
	// do nothing
}

UpdateRegistrationCommand::UpdateRegistrationCommand(const UpdateRegistrationCommand& urc)
	: pUpdatable(urc.pUpdatable)
{
	// do nothing
}

UpdateRegistrationCommand& UpdateRegistrationCommand::operator=(const UpdateRegistrationCommand& urc)
{
	pUpdatable = urc.pUpdatable;

	return *this;
}

void UpdateRegistrationCommand::Execute()
{
	UpdatableObjectAttorney::Registration::Register(pUpdatable);
}
