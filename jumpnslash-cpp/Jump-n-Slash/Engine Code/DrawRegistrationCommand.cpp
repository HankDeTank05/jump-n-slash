#include "DrawRegistrationCommand.h"

#include <cassert>
#include "DrawableObjectAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(DrawableObject* _pDrawObj)
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
	DrawableObjectAttorney::Registration::Register(pDrawable);
}
