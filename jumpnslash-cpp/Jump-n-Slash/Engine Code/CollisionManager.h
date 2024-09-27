#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

class CollisionManager
{
public:
	CollisionManager();
	CollisionManager(const CollisionManager& cm) = delete;
	CollisionManager& operator=(const CollisionManager& cm) = delete;
	virtual ~CollisionManager();
};

#endif