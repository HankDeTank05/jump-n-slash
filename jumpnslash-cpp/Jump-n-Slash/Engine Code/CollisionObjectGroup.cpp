#include "CollisionObjectGroup.h"

CollisionObjectGroup::CollisionObjectGroup()
	: collisionObjectList(),
	pGroupAABB(nullptr) // TODO: add group AABB functionality
{
}

CollisionObjectGroup::~CollisionObjectGroup()
{
	// do nothing (for now)
}

CollisionObjectGroup::CollisionObjectListRef CollisionObjectGroup::Register(CollisionObject* pCollidable)
{
	// TODO: do group AABB stuff here

	return collisionObjectList.insert(collisionObjectList.begin(), pCollidable);
}

void CollisionObjectGroup::Deregister(CollisionObjectListRef deleteRef)
{
	collisionObjectList.erase(deleteRef);
}

CollisionObjectGroup::CollisionObjectList CollisionObjectGroup::GetCollisionObjectList()
{
	return collisionObjectList;
}

bool CollisionObjectGroup::HasMembers()
{
	return collisionObjectList.size() > 0;
}

sf::FloatRect* CollisionObjectGroup::GetGroupAABB()
{
	return pGroupAABB;
}

void CollisionObjectGroup::ComputeData()
{
	// TODO: recompute group AABB here
	//assert(false);
}
