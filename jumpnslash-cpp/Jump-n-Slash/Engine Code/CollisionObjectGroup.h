#ifndef COLLISION_OBJECT_GROUP_H
#define COLLISION_OBJECT_GROUP_H

#include <list>

#include <SFML/Graphics/Rect.hpp>

// forward declarations
class CollisionObject;

class CollisionObjectGroup
{
public:
	CollisionObjectGroup();
	CollisionObjectGroup(const CollisionObjectGroup& cg) = delete;
	CollisionObjectGroup& operator=(const CollisionObjectGroup& cg) = delete;
	virtual ~CollisionObjectGroup();

	using CollisionObjectList = std::list<CollisionObject*>;
	using CollisionObjectListRef = CollisionObjectList::iterator;

	CollisionObjectListRef Register(CollisionObject* pCollidable);
	void Deregister(CollisionObjectListRef deleteRef);

	CollisionObjectList GetCollisionObjectList();
	bool HasMembers();
	sf::FloatRect* GetGroupAABB();
	void ComputeData();

private:
	CollisionObjectList collisionObjectList;
	sf::FloatRect* pGroupAABB;
};

#endif