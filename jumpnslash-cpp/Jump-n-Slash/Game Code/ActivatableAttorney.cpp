#include "ActivatableAttorney.h"

// game includes
#include "Activatable.h"

void ActivatableAttorney::ActivatorAccess::Activate(Activatable* pActivatable)
{
	pActivatable->Activate();
}
