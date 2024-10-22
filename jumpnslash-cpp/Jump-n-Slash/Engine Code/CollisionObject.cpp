#include "CollisionObject.h"

#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionObjectGroup.h"
#include "CollisionVolumeAABB.h"

CollisionObject::CollisionObject()
	: typeID(CollisionManager::JNSID_UNDEFINED),
	regState(RegistrationState::CURRENTLY_DEREGISTERED),
	deleteRef(),
	pRegCmd(new CollisionRegistrationCommand(this)),
	pDeregCmd(new CollisionDeregistrationCommand(this)),
	pColVol(nullptr),
	pVolType(nullptr),
	pColSpr(nullptr)
{
	// do nothing
}

CollisionObject::~CollisionObject()
{
	if (pColVol != nullptr) delete pColVol;
	delete pDeregCmd;
	delete pRegCmd;
}

const CollisionVolume& CollisionObject::GetCollisionVolume()
{
	assert(pColVol != nullptr); // did you ever call SetCollisionSprite()?
	return *pColVol;
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

void CollisionObject::SetCollisionSprite(sf::Sprite* pSprite, VolumeType colVolType)
{
	pColSpr = pSprite;
	pVolType = &colVolType;
	switch (colVolType)
	{
	case VolumeType::BSphere:
		assert(false);
		break;
	case VolumeType::AABB:
		pColVol = new CollisionVolumeAABB(pSprite->getGlobalBounds().getPosition(),
			pSprite->getGlobalBounds().getPosition() + pSprite->getGlobalBounds().getSize());
		break;
	case VolumeType::OBB:
		assert(false);
		break;
	default:
		assert(false);
	}
}

void CollisionObject::UpdateCollisionData(sf::Sprite* pSprite)
{
	pColSpr = pSprite; // TODO: doing this is necessary because of how animation works, which might invalidate the existence of pColSpr as a member variable. Consider removing it.
	pColVol->ComputeData(pColSpr, pColSpr->getTransform());
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
