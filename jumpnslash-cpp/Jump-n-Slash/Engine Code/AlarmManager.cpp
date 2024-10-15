#include "AlarmManager.h"

#include "TimeManager.h"
#include "AlarmObjectAttorney.h"

AlarmManager::TimelineRef AlarmManager::Register(float triggerTime, AlarmObject* pAlarmable, AlarmID id)
{
    return timeline.insert(std::pair<float, AlarmEvent>(time, AlarmEvent(pAlarmable, id)));
}

void AlarmManager::Deregister(TimelineRef timelineRef)
{
    timeline.erase(timelineRef);
}

void AlarmManager::ProcessAlarms()
{
    TimelineRef it = timeline.begin();

    while (timeline.empty() == false &&
        it != timeline.end() &&
        it->first <= TimeManager::GetCurrentEngineTime())
    {
        // reminder:
        //--------------------------------------------------
        //       it
        //         ->first     ->second
        //             |           |
        //             |    +------+-----------------------+
        //             |    |          .first      .second |
        //             |    |             |            |   |
        //             V    |             V            V   |
        // std::pair<float, std::pair<AlarmObject*, AlarmID>>

        AlarmObjectAttorney::GameLoop::TriggerAlarm(it->second.first, it->second.second);
        if (it != timeline.end())
        {
            it = timeline.erase(it); // this erases the object from the multimap and advances the iterator all at once
        }
    }
}
