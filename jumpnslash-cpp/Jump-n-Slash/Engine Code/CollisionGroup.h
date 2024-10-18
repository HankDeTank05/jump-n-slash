#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <list>

#include <SFML/Graphics/Rect.hpp>

// forward declarations
class CollisionObject;

class CollisionGroup
{
public:
	CollisionGroup();
	CollisionGroup(const CollisionGroup& cg) = delete;
	CollisionGroup& operator=(const CollisionGroup& cg) = delete;
	virtual ~CollisionGroup();

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
	sf::FloatRect* pGroupAABB
};

#endif