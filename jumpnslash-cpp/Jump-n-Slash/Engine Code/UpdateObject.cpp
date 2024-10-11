#include "UpdateObject.h"

#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

UpdateObject::UpdateObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new UpdateRegistrationCommand(this)),
	pDeregCmd(new UpdateDeregistrationCommand(this)),
	deleteRef()
{
}

UpdateObject::~UpdateObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void UpdateObject::Update(float deltaTime)
{
	// do nothing. override to make it do something
}

void UpdateObject::RequestUpdateRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void UpdateObject::RequestUpdateDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}

void UpdateObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Update::Register(SceneManager::GetCurrentScene(), this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void UpdateObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Update::Deregister(SceneManager::GetCurrentScene(), deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
