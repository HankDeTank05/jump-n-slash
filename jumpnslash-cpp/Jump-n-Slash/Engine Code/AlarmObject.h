#ifndef ALARM_OBJECT_H
#define ALARM_OBJECT_H

#include <array>

#include "../Game Code/Constants.h"
#include "RegistrationState.h"
#include "AlarmID.h"
#include "AlarmManager.h"

// forward declarations
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class AlarmObject
{
public:
	AlarmObject();
	AlarmObject(const AlarmObject& ao) = delete;
	AlarmObject& operator=(const AlarmObject& ao) = delete;
	virtual ~AlarmObject();

	virtual void Alarm0(); // TODO: docs for AlarmObject::Alarm0
	virtual void Alarm1(); // TODO: docs for AlarmObject::Alarm1
	virtual void Alarm2(); // TODO: docs for AlarmObject::Alarm2
	virtual void Alarm3(); // TODO: docs for AlarmObject::Alarm3
	virtual void Alarm4(); // TODO: docs for AlarmObject::Alarm4
	virtual void Alarm5(); // TODO: docs for AlarmObject::Alarm5
	virtual void Alarm6(); // TODO: docs for AlarmObject::Alarm6
	virtual void Alarm7(); // TODO: docs for AlarmObject::Alarm7
	virtual void Alarm8(); // TODO: docs for AlarmObject::Alarm8
	virtual void Alarm9(); // TODO: docs for AlarmObject::Alarm9

protected:
	void RequestAlarmRegistration(AlarmID id, float triggerTime); // TODO: docs for AlarmObject::RequestAlarmRegistration
	void RequestAlarmDeregistration(AlarmID id); // TODO: docs for AlarmObject::RequestAlarmDeregistration

private:
	friend class AlarmObjectAttorney;
	void TriggerAlarm(AlarmID id);

	void AlarmRegistration(AlarmID id);
	void AlarmDeregistration(AlarmID id);

private:
	struct RegistrationData
	{
		float triggerTime;
		RegistrationState regState;
		AlarmManager::TimelineRef deleteRef;
		AlarmRegistrationCommand* pRegCmd;
		AlarmDeregistrationCommand* pDeregCmd;
	};

private:
	std::array<RegistrationData, ALARM_COUNT> regData;
};

#endif