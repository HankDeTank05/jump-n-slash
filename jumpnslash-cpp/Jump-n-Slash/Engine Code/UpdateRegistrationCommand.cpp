#include "UpdateRegistrationCommand.h"

#include "UpdateObjectAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(UpdateObject* _pUpdatable)
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
	UpdateObjectAttorney::Registration::Register(pUpdatable);
}
