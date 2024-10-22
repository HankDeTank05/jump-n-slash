#ifndef COLLISION_VOLUME_BOUNDING_BOX_H
#define COLLISION_VOLUME_BOUNDING_BOX_H

#include "CollisionVolume.h"

class CollisionVolumeBoundingBox : public CollisionVolume
{
public:
	CollisionVolumeBoundingBox() = delete;
	CollisionVolumeBoundingBox(const sf::Transform& tform, const sf::Vector2f& min, const sf::Vector2f& max);
	CollisionVolumeBoundingBox(const CollisionVolumeBoundingBox& cvbb) = delete;
	CollisionVolumeBoundingBox& operator=(const CollisionVolumeBoundingBox& cvbb) = delete;
	virtual ~CollisionVolumeBoundingBox() = default;

	const sf::Transform& GetTransform() const;
	const sf::Vector2f& GetMin() const;
	const sf::Vector2f& GetMax() const;

	const sf::Vector2f& GetHalfDiagonal() const;
	const sf::Vector2f& GetWorldSpaceCenter() const;
	float GetScaleFactorSqr() const;

	virtual void ComputeData(sf::Sprite* pSprite, const sf::Transform& tform) = 0;
	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

private:
	sf::Transform tform;
	sf::Vector2f min;
	sf::Vector2f max;

	// stuff for collision testing
	sf::Vector2f halfDiag;
	sf::Vector2f worldSpaceCenter;
	float scaleFactorSqr;
};

#endif