#include "TimeManagerAttorney.h"

#include "TimeManager.h"

void TimeManagerAttorney::Termination::Terminate()
{
	TimeManager::Terminate();
}

void TimeManagerAttorney::Time::Start()
{
	TimeManager::Start();
}

void TimeManagerAttorney::Time::ProcessTime()
{
	TimeManager::ProcessTime();
}
