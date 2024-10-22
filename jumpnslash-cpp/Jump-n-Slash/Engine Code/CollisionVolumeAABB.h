#ifndef COLLISION_VOLUME_AABB_H
#define COLLISION_VOLUME_AABB_H

#include <SFML/Graphics/Rect.hpp>

#include "CollisionVolume.h"

class CollisionVolumeAABB : public CollisionVolume
{
public:
	CollisionVolumeAABB() = delete;
	CollisionVolumeAABB(sf::FloatRect aabb);
	CollisionVolumeAABB(const CollisionVolumeAABB& cva) = delete;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB& cva) = delete;
	virtual ~CollisionVolumeAABB() = default;
};

#endif