#include "Activatable.h"

Activatable::Activatable()
	: isActivated(false)
{
	// do nothing
}

void Activatable::Activate()
{
	isActivated = true;
	OnActivation();
}
