#include "CollisionManager.h"

#include "CollisionGroup.h"

CollisionGroup* CollisionManager::GetCollisionGroup(JNSTypeID id)
{
	// did you forget to call SetCollidableGroup<type>()?
	// did you properly deregister collision when switching scenes?
	assert(id < static_cast<int>(collisionGroupCollection.size()));
	assert(id >= 0);

	return collisionGroupCollection[id];
}

void CollisionManager::SetGroupForTypeID(JNSTypeID id)
{
	while (id >= static_cast<int>(collisionGroupCollection.size()))
	{
		collisionGroupCollection.push_back(new CollisionGroup());
	}
}
