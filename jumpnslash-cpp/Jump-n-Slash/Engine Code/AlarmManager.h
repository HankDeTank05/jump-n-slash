#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <map>

#include "AlarmID.h"

// forward declarations
class AlarmObject;

class AlarmManager
{
public:
	AlarmManager();
	AlarmManager(const AlarmManager& am) = delete;
	AlarmManager& operator=(const AlarmManager& am) = delete;
	virtual ~AlarmManager();

private:
	using AlarmEvent = std::pair<AlarmObject*, AlarmID>;
	using TimelineMap = std::multimap<float, AlarmEvent>;

public:
	using TimelineRef = TimelineMap::iterator;

	TimelineRef Register(float triggerTime, AlarmObject* pAlarmable, AlarmID id);
	void Deregister(TimelineRef timelineRef);

	void ProcessAlarms();

private:
	TimelineMap timeline;
};

#endif