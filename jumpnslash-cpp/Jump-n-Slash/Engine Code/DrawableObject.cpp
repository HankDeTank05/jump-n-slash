#include "DrawableObject.h"

#include <cassert>
#include "DrawRegistrationCommand.h"
#include "JumpSlashEngine.h"
#include "SceneAttorney.h"

DrawableObject::DrawableObject()
	: regState(RegistrationState::CURRENTLY_DEREGISTERED),
	pRegCmd(new DrawRegistrationCommand(this))
{
	// do nothing
}

DrawableObject::~DrawableObject()
{
	delete pRegCmd;
}

void DrawableObject::Draw()
{
	// do nothing here

	// this is the default behavior, but needs to be overloaded if something is to be drawn
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

	assert(false); // TODO: enqueue draw deregistration command here

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

	assert(false); // TODO: code goes here

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
