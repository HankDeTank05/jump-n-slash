#include "ControlSelection.h"

// game includes
#include "ControlSelector.h"

ControlSelection::ControlSelection()
	: pSelector(nullptr)
{
	// do nothing
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
