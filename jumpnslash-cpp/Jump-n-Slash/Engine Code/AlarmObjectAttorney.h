#ifndef ALARM_OBJECT_ATTORNEY_H
#define ALARM_OBJECT_ATTORNEY_H

#include "AlarmID.h"

// forward declarations
class AlarmObject;

class AlarmObjectAttorney
{
public:
	class GameLoop
	{
	private:
		friend class AlarmManager;
		static void TriggerAlarm(AlarmObject* pAlarmable, AlarmID id);
	};
	class Registration
	{
	private:
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
		static void Register(AlarmObject* pAlarmable, AlarmID id);
		static void Deregister(AlarmObject* pAlarmable, AlarmID id);
	};
};

#endif