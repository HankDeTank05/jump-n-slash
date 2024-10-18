#include "CollisionObject.h"

#include "SceneAttorney.h"
#include "SceneManager.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"

void CollisionObject::RequestCollisionRegistration()
{
	assert(regState == RegistrationState::CURRENTLY_DEREGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pRegCmd);

	regState = RegistrationState::PENDING_REGISTRATION;
}

void CollisionObject::RequestCollisionDeregistration()
{
	assert(regState == RegistrationState::CURRENTLY_REGISTERED);

	SceneAttorney::Commands::AddCommand(SceneManager::GetCurrentScene(), pDeregCmd);

	regState = RegistrationState::PENDING_DEREGISTRATION;
}
