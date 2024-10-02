#include "DrawObject.h"

#include <cassert>

#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "JumpSlashEngine.h"
#include "SceneAttorney.h"

DrawObject::DrawObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new DrawRegistrationCommand(this)),
	pDeregCmd(new DrawDeregistrationCommand(this)),
	deleteRef()
{
	// do nothing
}

DrawObject::~DrawObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void DrawObject::Draw()
{
	// do nothing. override to make it do something
}

void DrawObject::EnqueueForDrawRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void DrawObject::EnqueueForDrawDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}

void DrawObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Draw::Register(JumpSlashEngine::GetCurrentScene(), this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void DrawObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Draw::Deregister(JumpSlashEngine::GetCurrentScene(), deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
