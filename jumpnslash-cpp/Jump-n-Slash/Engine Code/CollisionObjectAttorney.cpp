#include "CollisionObjectAttorney.h"

#include "CollisionObject.h"

void CollisionObjectAttorney::Registration::Register(CollisionObject* pCollidable)
{
	pCollidable->Register();
}

void CollisionObjectAttorney::Registration::Deregister(CollisionObject* pCollidable)
{
	pCollidable->Deregister();
}

void CollisionObjectAttorney::ColDispatch::Collision(CollisionObject* pThis, CollisionObject* pOther)
{
	pThis->Collision(pOther);
}

void CollisionObjectAttorney::NoColDispatch::NoCollision(CollisionObject* pThis, CollisionObject* pOther)
{
	pThis->NoCollision(pOther);
}
