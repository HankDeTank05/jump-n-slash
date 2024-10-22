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

private:
	sf::Vector2f center;
	float radius;
};

#endif