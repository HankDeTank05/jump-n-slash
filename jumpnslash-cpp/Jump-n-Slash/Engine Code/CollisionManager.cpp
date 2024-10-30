#include "CollisionManager.h"

#include "CollisionObjectGroup.h"

CollisionManager::JNSTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
	: colObjGroupCollection(),
	colTestCmdList()
{
	// do nothing
}

CollisionManager::~CollisionManager()
{
	while (colObjGroupCollection.empty() == false)
	{
		delete colObjGroupCollection.back();
		colObjGroupCollection.pop_back();
	}

	while (colTestCmdList.empty() == false)
	{
		delete colTestCmdList.back();
		colTestCmdList.pop_back();
	}
}

void CollisionManager::ComputeData()
{
	for (CollisionObjectGroupCollection::iterator it = colObjGroupCollection.begin(); it != colObjGroupCollection.end(); it++)
	{
		(*it)->ComputeData();
	}
}

void CollisionManager::ProcessCollisions()
{
	for (CollisionTestCommandList::iterator it = colTestCmdList.begin(); it != colTestCmdList.end(); it++)
	{
		(*it)->Execute();
	}
}

CollisionObjectGroup* CollisionManager::GetObjectGroup(JNSTypeID id)
{
	// did you forget to call SetCollidableGroup<type>()?
	// did you properly deregister collision when switching scenes?
	assert(id < static_cast<int>(colObjGroupCollection.size()));
	assert(id >= 0);

	return colObjGroupCollection[id];
}

void CollisionManager::SetGroupForTypeID(JNSTypeID id)
{
	while (id >= static_cast<int>(colObjGroupCollection.size()))
	{
		colObjGroupCollection.push_back(new CollisionObjectGroup());
	}
}
