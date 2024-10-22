#ifndef COLLISION_VOLUME_BSPHERE_H
#define COLLISION_VOLUME_BSPHERE_H

#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere() = delete;
	CollisionVolumeBSphere(sf::Vector2f center, float radius);
	CollisionVolumeBSphere(const CollisionVolumeBSphere& cvbs) = delete;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere& cvbs) = delete;
	virtual ~CollisionVolumeBSphere() = default;

	const sf::Vector2f& GetCenter() const;
	float GetRadius() const;
	float GetRadiusSqr() const;

	virtual void ComputeData(sf::Sprite* pSprite, const sf::Transform& tform) override;
	virtual bool IntersectAccept(const CollisionVolume& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const override;

	virtual void DebugView(const sf::Color& color) const override;

private:
	sf::Vector2f center;
	float radius;
};

#endif