#include "DrawableObject.h"

#include <cassert>
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"
#include "JumpSlashEngine.h"
#include "SceneAttorney.h"

DrawableObject::DrawableObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new DrawRegistrationCommand(this)),
	pDeregCmd(new DrawDeregistrationCommand(this)),
	deleteRef()
{
	// do nothing
}

DrawableObject::~DrawableObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

void DrawableObject::Draw()
{
	// do nothing. override to make it do something
}

void DrawableObject::EnqueueForDrawRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void DrawableObject::EnqueueForDrawDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(JumpSlashEngine::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}

void DrawableObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Draw::Register(JumpSlashEngine::GetCurrentScene(), this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void DrawableObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Draw::Deregister(JumpSlashEngine::GetCurrentScene(), deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}