#ifndef COLLISION_OBJECT_ATTORNEY_H
#define COLLISION_OBJECT_ATTORNEY_H

// forward declarations
class CollisionObject;

class CollisionObjectAttorney
{
public:
	class Registration
	{
	private:
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;
		static void Register(CollisionObject* pCollidable);
		static void Deregister(CollisionObject* pCollidable);
	};
	class ColDispatch
	{
	private:
		template <typename C1, typename C2>
		friend class CollisionDispatch;
		static void Collision(CollisionObject* pThis, CollisionObject* pOther);
	};
	class NoColDispatch
	{
	private:
		template <typename C1, typename C2>
		friend class NoCollisionDispatch;
		static void NoCollision(CollisionObject* pThis, CollisionObject* pOther);
	};
};

#endif