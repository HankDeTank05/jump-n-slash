#include "AlarmDeregistrationCommand.h"

#include "AlarmObjectAttorney.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(AlarmObject* _pAlarmable, AlarmID _id)
	: pAlarmable(_pAlarmable),
	id(_id)
{
	// do nothing
}

void AlarmDeregistrationCommand::Execute()
{
	AlarmObjectAttorney::Registration::Deregister(pAlarmable, id);
}
