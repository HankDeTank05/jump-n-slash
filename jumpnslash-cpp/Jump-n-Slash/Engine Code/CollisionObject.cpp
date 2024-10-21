#include "CollisionObject.h"

#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionObjectGroup.h"

CollisionObject::CollisionObject()
	: typeID(CollisionManager::JNSID_UNDEFINED),
	regState(RegistrationState::CURRENTLY_DEREGISTERED),
	deleteRef(),
	pRegCmd(new CollisionRegistrationCommand(this)),
	pDeregCmd(new CollisionDeregistrationCommand(this))
{
	// do nothing
}

CollisionObject::~CollisionObject()
{
	delete pDeregCmd;
	delete pRegCmd;
}

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

void CollisionObject::Register()
{
	assert(regState == RegistrationState::PENDING_REGISTRATION);

	deleteRef = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetObjectGroup(typeID)->Register(this);

	regState = RegistrationState::CURRENTLY_REGISTERED;
}

void CollisionObject::Deregister()
{
	assert(regState == RegistrationState::PENDING_DEREGISTRATION);

	SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetObjectGroup(typeID)->Deregister(deleteRef);

	regState = RegistrationState::CURRENTLY_DEREGISTERED;
}
