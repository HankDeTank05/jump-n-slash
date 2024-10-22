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
};

#endif