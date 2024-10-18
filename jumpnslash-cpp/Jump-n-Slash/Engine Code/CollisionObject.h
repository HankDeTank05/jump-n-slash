#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include "CollisionManager.h"
#include "RegistrationState.h"

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
		typeID = SceneAttorney::Collision::GetCollisionManager()->GetTypeID<C>():
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
	// collision list deleteref
	CollisionRegistrationCommand* pRegCmd;
	CollisionDeregistrationCommand* pDeregCmd;

};

#endif