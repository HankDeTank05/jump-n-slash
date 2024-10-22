#ifndef COLLISION_VOLUME_AABB_H
#define COLLISION_VOLUME_AABB_H

#include <SFML/Graphics/Rect.hpp>

#include "CollisionVolumeBoundingBox.h"

class CollisionVolumeAABB : public CollisionVolumeBoundingBox
{
public:
	CollisionVolumeAABB() = delete;
	CollisionVolumeAABB(const sf::Vector2f& min, const sf::Vector2f& max);
	CollisionVolumeAABB(const CollisionVolumeAABB& cva) = delete;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB& cva) = delete;
	virtual ~CollisionVolumeAABB() = default;

	const sf::Vector2f& GetMin() const;
	const sf::Vector2f& GetMax() const;

	virtual void ComputeData(sf::Sprite* pSprite, const sf::Transform& tform) override;
	virtual bool IntersectAccept(const CollisionVolume& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	virtual void DebugView(const sf::Color& color) const override;
};

#endif