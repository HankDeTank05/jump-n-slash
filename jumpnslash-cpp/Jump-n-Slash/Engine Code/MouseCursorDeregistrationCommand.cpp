#include "MouseCursorDeregistrationCommand.h"

#include "InputObjectAttorney.h"

MouseCursorDeregistrationCommand::MouseCursorDeregistrationCommand(InputObject* _pInputable)
	: pInputable(_pInputable)
{
	// do nothing
}

MouseCursorDeregistrationCommand::MouseCursorDeregistrationCommand(const MouseCursorDeregistrationCommand& mcdc)
	: pInputable(mcdc.pInputable)
{
	// do nothing
}

MouseCursorDeregistrationCommand& MouseCursorDeregistrationCommand::operator=(const MouseCursorDeregistrationCommand& mcdc)
{
	pInputable = mcdc.pInputable;

	return *this;
}

void MouseCursorDeregistrationCommand::Execute()
{
	InputObjectAttorney::Registration::DeregisterMouseCursor(pInputable);
}
