#include "ControlSelection.h"

#include "ControlSelector.h"

ControlSelection::ControlSelection()
	: pSelector(nullptr)
{
}

void ControlSelection::Init()
{
	assert(pSelector == nullptr);
	pSelector = new ControlSelector();
}

void ControlSelection::End()
{
	delete pSelector;
}
