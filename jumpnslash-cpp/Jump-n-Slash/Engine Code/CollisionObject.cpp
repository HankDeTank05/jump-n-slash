#include "CollisionObject.h"

#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionObjectGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

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
	if (colVolType == VolumeType::BSphere)
	{
		// 1. get sprite obb (pSprite->getLocalBounds())
		sf::FloatRect obb = pSprite->getLocalBounds();

		// 2. get the center point of the obb
		sf::Vector2f obbCenter = obb.getPosition() + (obb.getSize() * 0.5f);

		// 3. get the vector from the center of the obb to a corner
		sf::Vector2f centerToCorner = obb.getPosition() - obbCenter;

		// 4. transform that vector into world space (tform.transformPoint(vect))
		sf::Vector2f centerToCornerWS = pSprite->getTransform() * centerToCorner;

		// 5. get the magnitude of that vector	
		// 6. set it as the bsphere radius
		float radius = sqrtf(centerToCornerWS.x * centerToCornerWS.x + centerToCornerWS.y * centerToCornerWS.y);

		// 7. transform the center point into world space
		// 8. set it as the bsphere center
		sf::Vector2f center = pSprite->getTransform() * obbCenter;
		pColVol = new CollisionVolumeBSphere(center, radius);
	}
	else if (colVolType == VolumeType::AABB)
	{
		sf::Vector2f min = pSprite->getGlobalBounds().getPosition();
		sf::Vector2f max = min + pSprite->getGlobalBounds().getSize();
		pColVol = new CollisionVolumeAABB(min, max);
	}
	else if (colVolType == VolumeType::OBB)
	{
		assert(false);
	}
	else
	{
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
