#include "AlarmRegistrationCommand.h"

#include "AlarmObjectAttorney.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(AlarmObject* _pAlarmable, AlarmID _id)
	: pAlarmable(_pAlarmable),
	id(_id)
{
	// do nothing
}

void AlarmRegistrationCommand::Execute()
{
	AlarmObjectAttorney::Registration::Register(pAlarmable, id);
}
