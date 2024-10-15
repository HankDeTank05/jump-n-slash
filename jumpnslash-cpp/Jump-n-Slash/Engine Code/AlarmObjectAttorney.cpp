#include "AlarmObjectAttorney.h"

#include "AlarmObject.h"

void AlarmObjectAttorney::Registration::Register(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->AlarmRegistration(id);
}

void AlarmObjectAttorney::Registration::Deregister(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->AlarmDeregistration(id);
}

void AlarmObjectAttorney::GameLoop::TriggerAlarm(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->TriggerAlarm(id);
}
