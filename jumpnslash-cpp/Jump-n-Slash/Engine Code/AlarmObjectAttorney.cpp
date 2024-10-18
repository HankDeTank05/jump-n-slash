#include "AlarmObjectAttorney.h"

#include "AlarmObject.h"

void AlarmObjectAttorney::Registration::Register(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->Register(id);
}

void AlarmObjectAttorney::Registration::Deregister(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->Deregister(id);
}

void AlarmObjectAttorney::GameLoop::TriggerAlarm(AlarmObject* pAlarmable, AlarmID id)
{
	pAlarmable->TriggerAlarm(id);
}
