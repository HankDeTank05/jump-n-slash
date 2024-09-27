#include "UpdatableObject.h"

#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"
#include "SceneAttorney.h"
#include "JumpSlashEngine.h"

UpdatableObject::UpdatableObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new UpdateRegistrationCommand(this)),
	pDeregCmd(new UpdateDeregistrationCommand(this)),
	deleteRef()
{
}

UpdatableObject::~UpdatableObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void UpdatableObject::Update(float deltaTime)
{
	// do nothing. override to make it do something
}

void UpdatableObject::EnqueueForUpdateRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void UpdatableObject::EnqueueForUpdateDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}

void UpdatableObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Update::Register(JumpSlashEngine::GetCurrentScene(), this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void UpdatableObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Update::Deregister(JumpSlashEngine::GetCurrentScene(), deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
