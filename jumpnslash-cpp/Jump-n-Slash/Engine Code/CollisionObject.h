#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include <SFML/Graphics/Sprite.hpp>

#include "CollisionManager.h"
#include "CollisionObjectGroup.h"
#include "RegistrationState.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

// forward declarations
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class CollisionVolume;

class CollisionObject
{
public:
	CollisionObject();
	CollisionObject(const CollisionObject& co) = delete;
	CollisionObject& operator=(const CollisionObject& co) = delete;
	virtual ~CollisionObject();

	const CollisionVolume& GetCollisionVolume(); // TODO: docs for CollisionObject::GetCollisionVolume


protected:
	enum class VolumeType
	{
		BSphere,
		AABB
	};

	template <typename C>
	void SetCollidableGroup()
	{
		typeID = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetTypeID<C>();
	}
	
	void RequestCollisionRegistration(); // TODO: docs for CollisionObject::RequestCollisionRegistration
	void RequestCollisionDeregistration(); // TODO: docs for CollisionObject::RequestCollisionDeregistration

	void SetCollisionSprite(sf::Sprite* pSprite, VolumeType colVolType); // TODO: docs for CollisionObject::SetCollisionSprite
	void UpdateCollisionData(sf::Sprite* pSprite); // TODO: docs for CollisionObject::UpdateCollisionData

	virtual void OnCollisionEnter(CollisionObject* pOther);
	virtual void OnCollisionDuring(CollisionObject* pOther);
	virtual void OnCollisionExit(CollisionObject* pOther);

private:
	friend class CollisionObjectAttorney;
	void Register();
	void Deregister();

	void Collision(CollisionObject* pOther);
	void NoCollision(CollisionObject* pOther);

private: // member variables
	CollisionManager::JNSTypeID typeID;
	RegistrationState regState;
	CollisionObjectGroup::CollisionObjectListRef deleteRef;
	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;
	CollisionVolume* pColVol;
	VolumeType* pVolType;
	sf::Sprite* pColSpr;
	bool collisionThisFrame;
	bool collisionPrevFrame;

};

#endif