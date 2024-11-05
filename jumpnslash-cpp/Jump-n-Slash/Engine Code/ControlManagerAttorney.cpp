#include "ControlManagerAttorney.h"

#include "ControlManager.h"

void ControlManagerAttorney::EngineAccess::Terminate()
{
	ControlManager::Terminate();
}
