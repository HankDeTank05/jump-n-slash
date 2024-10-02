#include "UpdateDeregistrationCommand.h"

#include "UpdateObjectAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(UpdateObject* _pUpdatable)
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
	UpdateObjectAttorney::Registration::Deregister(pUpdatable);
}
