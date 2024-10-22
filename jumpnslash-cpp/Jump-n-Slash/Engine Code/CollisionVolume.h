#ifndef COLLISION_VOLUME_H
#define COLLISION_VOLUME_H

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

// forward declarations
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume& cv) = delete;
	CollisionVolume& operator=(const CollisionVolume& cv) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(sf::Sprite* pSprite, const sf::Transform& tform) = 0;
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

	virtual void DebugView(const sf::Color& color) const = 0;
};

#endif