#include "UpdateDeregistrationCommand.h"

#include "UpdatableObjectAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(UpdatableObject* _pUpdatable)
	: pUpdatable(_pUpdatable)
{
	// do nothing
}

UpdateDeregistrationCommand::UpdateDeregistrationCommand(const UpdateDeregistrationCommand& udc)
	: pUpdatable(udc.pUpdatable)
{
	// do nothing
}

UpdateDeregistrationCommand& UpdateDeregistrationCommand::operator=(const UpdateDeregistrationCommand& udc)
{
	pUpdatable = udc.pUpdatable;

	return *this;
}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableObjectAttorney::Registration::Deregister(pUpdatable);
}