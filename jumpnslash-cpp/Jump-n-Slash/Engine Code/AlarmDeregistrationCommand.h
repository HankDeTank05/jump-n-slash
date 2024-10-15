#ifndef ALARM_DEREGISTRATION_COMMAND_H
#define ALARM_DEREGISTRATION_COMMAND_H

#include "Command.h"
#include "AlarmID.h"

// forward declarations
class AlarmObject;

class AlarmDeregistrationCommand : public Command
{
public:
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(AlarmObject* pAlarmable, AlarmID id);
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand& adc) = delete;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand& adc) = delete;
	virtual ~AlarmDeregistrationCommand() = default;

	virtual void Execute() override;

private:
	AlarmObject* pAlarmable;
	AlarmID id;
};

#endif