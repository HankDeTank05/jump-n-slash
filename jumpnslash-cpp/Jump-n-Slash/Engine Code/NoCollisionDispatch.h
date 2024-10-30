#ifndef NO_COLLISION_DISPATCH_H
#define NO_COLLISION_DISPATCH_H

#include "CollisionDispatchBase.h"
#include "CollisionObjectAttorney.h"

// forward declarations
class CollisionObject;

template <typename C1, typename C2>
class NoCollisionDispatch : public CollisionDispatchBase
{
public:
	NoCollisionDispatch() = default;
	NoCollisionDispatch(const NoCollisionDispatch& ncd) = delete;
	NoCollisionDispatch& operator=(const NoCollisionDispatch& ncd) = delete;
	virtual ~NoCollisionDispatch() = default;

	virtual void ProcessCallbacks(CollisionObject* pCollidable1, CollisionObject* pCollidable2) override
	{
		// see also http://www.drdobbs.com/casting-in-c/184403316
		C1* pDerivedCollidable1 = static_cast<C1*>(pCollidable1);
		C2* pDerivedCollidable2 = static_cast<C2*>(pCollidable2);

		//pDerivedCollidable1->NoCollision(pDerivedCollidable2);
		//pDerivedCollidable2->NoCollision(pDerivedCollidable1);
		CollisionObjectAttorney::NoColDispatch::NoCollision(pDerivedCollidable1, pDerivedCollidable2);
		CollisionObjectAttorney::NoColDispatch::NoCollision(pDerivedCollidable2, pDerivedCollidable1);
	}
};

#endif