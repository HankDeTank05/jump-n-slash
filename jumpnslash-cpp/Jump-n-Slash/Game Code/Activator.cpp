#include "Activator.h"

// game includes
#include "ActivatableAttorney.h"

Activator::Activator(Activatable* _pThingToActivate)
	: pThingToActivate(_pThingToActivate),
	isTriggered(false)
{
	assert(pThingToActivate != nullptr);
}

void Activator::Trigger()
{
	ActivatableAttorney::ActivatorAccess::Activate(pThingToActivate);
}
