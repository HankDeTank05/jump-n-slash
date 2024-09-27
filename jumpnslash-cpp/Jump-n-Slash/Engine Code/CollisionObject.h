#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

class CollisionObject
{
public:
	CollisionObject();
	CollisionObject(const CollisionObject& co) = delete;
	CollisionObject& operator=(const CollisionObject& co) = delete;
	virtual ~CollisionObject();

};

#endif