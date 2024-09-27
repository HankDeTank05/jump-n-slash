#include "MouseCursorRegistrationCommand.h"

#include "InputObjectAttorney.h"

MouseCursorRegistrationCommand::MouseCursorRegistrationCommand(InputObject* _pInputable)
	: pInputable(_pInputable)
{
	// do nothing
}

MouseCursorRegistrationCommand::MouseCursorRegistrationCommand(const MouseCursorRegistrationCommand& mcrc)
	: pInputable(mcrc.pInputable)
{
	// do nothing
}

MouseCursorRegistrationCommand& MouseCursorRegistrationCommand::operator=(const MouseCursorRegistrationCommand& mcrc)
{
	pInputable = mcrc.pInputable;

	return *this;
}

void MouseCursorRegistrationCommand::Execute()
{
	InputObjectAttorney::Registration::RegisterMouseCursor(pInputable);
}
