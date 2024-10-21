#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include "CollisionManager.h"
#include "CollisionObjectGroup.h"
#include "RegistrationState.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

// forward declarations
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;

class CollisionObject
{
public:
	CollisionObject();
	CollisionObject(const CollisionObject& co) = delete;
	CollisionObject& operator=(const CollisionObject& co) = delete;
	virtual ~CollisionObject();

protected:

	template <typename C>
	void SetCollidableGroup()
	{
		typeID = SceneAttorney::Collision::GetCollisionManager(SceneManager::GetCurrentScene())->GetTypeID<C>();
	}
	
	void RequestCollisionRegistration(); // TODO: docs for CollisionObject::RequestCollisionRegistration
	void RequestCollisionDeregistration(); // TODO: docs for CollisionObject::RequestCollisionDeregistration

private:
	friend class CollisionObjectAttorney;
	void Register();
	void Deregister();

private: // member variables
	CollisionManager::JNSTypeID typeID;
	RegistrationState regState;
	CollisionObjectGroup::CollisionObjectListRef deleteRef;
	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;

};

#endif