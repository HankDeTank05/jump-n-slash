#include "AlarmObject.h"

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

AlarmObject::AlarmObject()
	: regData()
{
	for (int i = 0; i < ALARM_COUNT; i++)
	{
		regData[i].triggerTime = -1.f;
		regData[i].regState = RegistrationState::CURRENTLY_DEREGISTERED;
		assert(false); // create alarm registration command
		assert(false); // create alarm deregistration command
	}
}

AlarmObject::~AlarmObject()
{
	for (int i = 0; i < ALARM_COUNT; i++)
	{
		delete regData[i].pDeregCmd; assert(false); // remove this when the alarm deregistration command is new'd
		delete regData[i].pRegCmd; assert(false); // remove this when the alarm registration command is new'd
	}
}

void AlarmObject::Alarm0()
{
	// do nothing
}

void AlarmObject::Alarm1()
{
	// do nothing
}

void AlarmObject::Alarm2()
{
	// do nothing
}

void AlarmObject::Alarm3()
{
	// do nothing
}

void AlarmObject::Alarm4()
{
	// do nothing
}

void AlarmObject::Alarm5()
{
	// do nothing
}

void AlarmObject::Alarm6()
{
	// do nothing
}

void AlarmObject::Alarm7()
{
	// do nothing
}

void AlarmObject::Alarm8()
{
	// do nothing
}

void AlarmObject::Alarm9()
{
	// do nothing
}

void AlarmObject::RequestAlarmRegistration(AlarmID id, float triggerTime)
{
	int alarmNum = static_cast<int>(id);

	assert(regData[alarmNum].regState == RegistrationState::CURRENTLY_DEREGISTERED);

	regData[alarmNum].triggerTime = triggerTime;
	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), regData[alarmNum].pRegCmd);

	regData[alarmNum].regState = RegistrationState::PENDING_REGISTRATION;
}

void AlarmObject::RequestAlarmDeregistration(AlarmID id)
{
	int alarmNum = static_cast<int>(id);

	assert(regData[alarmNum].regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), regData[alarmNum].pDeregCmd);

	regData[alarmNum].regState = RegistrationState::PENDING_DEREGISTRATION;
}

void AlarmObject::TriggerAlarm(AlarmID id)
{
	switch (id)
	{
	case AlarmID::Alarm0:
		Alarm0();
		break;
	case AlarmID::Alarm1:
		Alarm1();
		break;
	case AlarmID::Alarm2:
		Alarm2();
		break;
	case AlarmID::Alarm3:
		Alarm3();
		break;
	case AlarmID::Alarm4:
		Alarm4();
		break;
	case AlarmID::Alarm5:
		Alarm5();
		break;
	case AlarmID::Alarm6:
		Alarm6();
		break;
	case AlarmID::Alarm7:
		Alarm7();
		break;
	case AlarmID::Alarm8:
		Alarm8();
		break;
	case AlarmID::Alarm9:
		Alarm9();
		break;
	default:
		assert(false); // silly goose! adding more alarms is more complicated than you thought!
	}
}

void AlarmObject::AlarmRegistration(AlarmID id)
{
	int alarmNum = static_cast<int>(id);

	assert(regData[alarmNum].regState == RegistrationState::PENDING_REGISTRATION);

	regData[alarmNum].deleteRef = SceneAttorney::Alarm::Register(SceneManager::GetCurrentScene(), regData[alarmNum].triggerTime, this, id);

	regData[alarmNum].regState = RegistrationState::CURRENTLY_REGISTERED;
}

void AlarmObject::AlarmDeregistration(AlarmID id)
{
	int alarmNum = static_cast<int>(id);

	assert(regData[alarmNum].regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Alarm::Deregister(SceneManager::GetCurrentScene(), regData[alarmNum].deleteRef);

	regData[alarmNum].regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
