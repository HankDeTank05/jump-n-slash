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
