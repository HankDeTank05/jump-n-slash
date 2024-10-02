#include "DrawDeregistrationCommand.h"

#include <cassert>

#include "DrawObjectAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(DrawObject* _pDrawable)
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
	DrawObjectAttorney::Registration::Deregister(pDrawable);
}
