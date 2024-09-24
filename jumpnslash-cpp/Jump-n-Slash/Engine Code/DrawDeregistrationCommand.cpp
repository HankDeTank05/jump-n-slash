#include "DrawDeregistrationCommand.h"

#include "DrawableObjectAttorney.h"
#include <cassert>

DrawDeregistrationCommand::DrawDeregistrationCommand(DrawableObject* _pDrawable)
	: pDrawable(_pDrawable)
{
	// do nothing
}

DrawDeregistrationCommand::DrawDeregistrationCommand(const DrawDeregistrationCommand& ddc)
	: pDrawable(ddc.pDrawable)
{
	// do nothing
}

DrawDeregistrationCommand& DrawDeregistrationCommand::operator=(const DrawDeregistrationCommand& ddc)
{
	pDrawable = ddc.pDrawable;

	return *this;
}

void DrawDeregistrationCommand::Execute()
{
	assert(false);
}
