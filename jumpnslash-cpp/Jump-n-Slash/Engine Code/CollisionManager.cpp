#include "CollisionManager.h"

#include "CollisionObjectGroup.h"

CollisionManager::CollisionManager()
	: collObjGroupCollection(),
	colTestCmdList()
{
	// do nothing
}

CollisionManager::~CollisionManager()
{
	while (collObjGroupCollection.empty() == false)
	{
		delete collObjGroupCollection.back();
		collObjGroupCollection.pop_back();
	}

	while (colTestCmdList.empty() == false)
	{
		delete colTestCmdList.back();
		colTestCmdList.pop_back();
	}
}

void CollisionManager::ComputeData()
{
	assert(false);
}

void CollisionManager::ProcessCollisions()
{
	assert(false);
}

CollisionObjectGroup* CollisionManager::GetObjectGroup(JNSTypeID id)
{
	// did you forget to call SetCollidableGroup<type>()?
	// did you properly deregister collision when switching scenes?
	assert(id < static_cast<int>(collObjGroupCollection.size()));
	assert(id >= 0);

	return collObjGroupCollection[id];
}

void CollisionManager::SetGroupForTypeID(JNSTypeID id)
{
	while (id >= static_cast<int>(collObjGroupCollection.size()))
	{
		collObjGroupCollection.push_back(new CollisionObjectGroup());
	}
}
