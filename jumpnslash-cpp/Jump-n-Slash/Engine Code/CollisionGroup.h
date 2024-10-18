#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

class CollisionGroup
{
public:
	CollisionGroup();
	CollisionGroup(const CollisionGroup& cg) = delete;
	CollisionGroup& operator=(const CollisionGroup& cg) = delete;
	virtual ~CollisionGroup();
};

#endif