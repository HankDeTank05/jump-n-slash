#ifndef COLLISION_DISPATCH_H
#define COLLISION_DISPATCH_H

#include "CollisionDispatchBase.h"
#include "CollisionObjectAttorney.h"

// forward declarations
class CollisionObject;

template <typename C1, typename C2>
class CollisionDispatch : public CollisionDispatchBase
{
public:
	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch& cd) = delete;
	CollisionDispatch& operator=(const CollisionDispatch& cd) = delete;
	virtual ~CollisionDispatch() = default;

	virtual void ProcessCallbacks(CollisionObject* pCollidable1, CollisionObject* pCollidable2) override
	{
		// see also http://www.drdobbs.com/casting-in-c/184403316
		C1* pDerivedCollidable1 = static_cast<C1*>(pCollidable1);
		C2* pDerivedCollidable2 = static_cast<C2*>(pCollidable2);

		//pDerivedCollidable1->Collision(pDerivedCollidable2);
		//pDerivedCollidable2->Collision(pDerivedCollidable1);
		CollisionObjectAttorney::ColDispatch::Collision(pDerivedCollidable1, pDerivedCollidable2);
		CollisionObjectAttorney::ColDispatch::Collision(pDerivedCollidable2, pDerivedCollidable1);
	}
};

#endif