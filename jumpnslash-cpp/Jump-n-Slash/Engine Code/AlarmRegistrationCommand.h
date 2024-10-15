#ifndef ALARM_REGISTRATION_COMMAND_H
#define ALARM_REGISTRATION_COMMAND_H

#include "Command.h"
#include "AlarmID.h"

// forward declarations
class AlarmObject;

class AlarmRegistrationCommand : public Command
{
public:
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(AlarmObject* pAlarmable, AlarmID id);
	AlarmRegistrationCommand(const AlarmRegistrationCommand& arc) = delete;
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand& arc) = delete;
	virtual ~AlarmRegistrationCommand() = default;

	virtual void Execute() override;

private:
	AlarmObject* pAlarmable;
	AlarmID id;
};

#endif