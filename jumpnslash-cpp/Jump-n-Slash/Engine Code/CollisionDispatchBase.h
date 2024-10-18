#ifndef COLLISION_DISPATCH_BASE_H
#define COLLISION_DISPATCH_BASE_H

// forward declarations
class CollisionObject;

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase& cdb) = delete;
	CollisionDispatchBase& operator=(const CollisionDispatchBase& cdb) = delete;
	virtual ~CollisionDispatchBase() = default;

	virtual void ProcessCallbacks(CollisionObject* pCollidable1, CollisionObject* pCollidable2) = 0;
};

#endif