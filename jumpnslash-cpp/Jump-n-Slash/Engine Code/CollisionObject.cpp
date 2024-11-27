#include "CollisionObject.h"

// engine includes
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionObjectGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "Math.h"
#include "SpriteAttorney.h"
#include "Sprite.h"

CollisionObject::CollisionObject()
	: typeID(CollisionManager::JNSID_UNDEFINED),
	regState(RegistrationState::CURRENTLY_DEREGISTERED),
	deleteRef(),
	pRegCmd(new CollisionRegistrationCommand(this)),
	pDeregCmd(new CollisionDeregistrationCommand(this)),
	pColVol(nullptr),
	pVolType(nullptr),
	pColSpr(nullptr),
	collisionThisFrame(false),
	collisionPrevFrame(false)
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

void CollisionObject::SetCollisionSprite(Sprite* pSprite, VolumeType colVolType)
{
	pColSpr = pSprite;
	pVolType = &colVolType;
	if (colVolType == VolumeType::BSphere)
	{
		sf::Vector2f aabbPos = pColSpr->GetLocalBounds().getPosition();
		sf::Vector2f aabbSize = pColSpr->GetLocalBounds().getSize();
		sf::Vector2f center = aabbPos + aabbSize * 0.5f;
		float radius = Math::Max(aabbSize.x, aabbSize.y) * 0.5f;
		pColVol = new CollisionVolumeBSphere(center, radius);
	}
	else if (colVolType == VolumeType::AABB)
	{
		sf::Vector2f min = pColSpr->GetGlobalBounds().getPosition();
		sf::Vector2f max = min + pColSpr->GetGlobalBounds().getSize();
		pColVol = new CollisionVolumeAABB(min, max);
	}
	else
	{
		assert(false);
	}
}

void CollisionObject::UpdateCollisionData()
{
	pColVol->ComputeData(pColSpr, pColSpr->GetTransform());
}

void CollisionObject::UpdateCollisionData(Sprite* pSprite)
{
	// TODO: doing this is necessary because of how animation works, which might invalidate the existence of pColSpr as a member variable. Consider removing it.
	pColSpr = pSprite;
	UpdateCollisionData();
}

void CollisionObject::Collision(CollisionObject* pOther)
{
	collisionPrevFrame = collisionThisFrame;
	collisionThisFrame = true;

	if (collisionPrevFrame == true && collisionThisFrame == true)
	{
		OnCollisionDuring(pOther);
	}
	else if (collisionPrevFrame == false && collisionThisFrame == true)
	{
		OnCollisionEnter(pOther);
	}
}

void CollisionObject::NoCollision(CollisionObject* pOther)
{
	collisionPrevFrame = collisionThisFrame;
	collisionThisFrame = false;

	if (collisionPrevFrame == true && collisionThisFrame == false)
	{
		OnCollisionExit(pOther);
	}
}

void CollisionObject::OnCollisionEnter(CollisionObject* pOther)
{
	// do nothing. override to make it do something
}

void CollisionObject::OnCollisionDuring(CollisionObject* pOther)
{
	// do nothing. override to make it do something
}

void CollisionObject::OnCollisionExit(CollisionObject* pOther)
{
	// do nothing. override to make it do something
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
