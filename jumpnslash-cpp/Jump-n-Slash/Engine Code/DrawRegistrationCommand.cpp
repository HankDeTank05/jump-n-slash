#include "DrawRegistrationCommand.h"

#include <cassert>

#include "DrawObjectAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(DrawObject* _pDrawObj)
	: pDrawable(_pDrawObj)
{
	// do nothing
}

DrawRegistrationCommand::DrawRegistrationCommand(const DrawRegistrationCommand& drc)
	: pDrawable(drc.pDrawable)
{
	// do nothing
}

DrawRegistrationCommand& DrawRegistrationCommand::operator=(const DrawRegistrationCommand& drc)
{
	pDrawable = drc.pDrawable;

	return *this;
}

void DrawRegistrationCommand::Execute()
{
	DrawObjectAttorney::Registration::Register(pDrawable);
}
