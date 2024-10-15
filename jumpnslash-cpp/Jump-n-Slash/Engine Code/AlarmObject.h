#ifndef ALARM_OBJECT_H
#define ALARM_OBJECT_H

class AlarmObject
{
public:
	AlarmObject();
	AlarmObject(const AlarmObject& ao) = delete;
	AlarmObject& operator=(const AlarmObject& ao) = delete;
	virtual ~AlarmObject();

protected:
	void RequestAlarmRegistration();
	void RequestAlarmDeregistration();

};

#endif