#ifndef MATH_H
#define MATH_H

#include <SFML/System/Vector2.hpp>

// forward declarations
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class Math
{
public:

	// collision detection functions

	// generic collision volume intersection test
	static bool Intersect(const CollisionVolume& a, const CollisionVolume& b); // TODO: docs for Math::Intersect(volume, volume)

	// BSphere vs. BSphere
	static bool Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2); // TODO: docs for intersect bs/bs
	// BSphere vs. AABB
	static bool Intersect(const CollisionVolumeBSphere& bs, const CollisionVolumeAABB& aabb); // TODO: docs for intersect bs/aabb
	// BSphere vs. OBB
	static bool Intersect(const CollisionVolumeBSphere& bs, const CollisionVolumeOBB& obb); // TODO: docs for intersect bs/obb
	// AABB vs. BSphere
	static bool Intersect(const CollisionVolumeAABB& aabb, const CollisionVolumeBSphere& bs); // TODO: docs for intersect aabb/bs
	// AABB vs. AABB
	static bool Intersect(const CollisionVolumeAABB& aabb1, const CollisionVolumeAABB& aabb2); // TODO: docs for intersect aabb/aabb
	// AABB vs. OBB
	static bool Intersect(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb); // TODO: docs for intersect aabb/obb
	// OBB vs. BSphere
	static bool Intersect(const CollisionVolumeOBB& obb, const CollisionVolumeBSphere& bs); // TODO: docs for intersect obb/bs
	// OBB vs. AABB
	static bool Intersect(const CollisionVolumeOBB& obb, const CollisionVolumeAABB& aabb); // TODO: docs for intersect obb/aabb
	// OBB vs. OBB
	static bool Intersect(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2); // TODO: docs for intersect obb/obb
	
	// general math support functions

	static float ClampValue(float valToClamp, float clampMin, float clampMax); // TODO: docs for Math::ClampValue
	static sf::Vector2f ClampPoint(sf::Vector2f toClamp, sf::Vector2f clampMin, sf::Vector2f clampMax); // TODO: docs for Math::ClampPoint
	static sf::Vector2i ConvertWorldToScreenSpace(sf::Vector2f worldSpaceCoords); // TODO: docs for Math::ConvertWorldToScreenSpace
	static sf::Vector2f ConvertScreenToWorldSpace(sf::Vector2i screenSpaceCoords); // TODO: docs for Math::ConvertScreenToWorldSpace
	static bool IntervalOverlap(float min0, float max0, float min1, float max1); // TODO: docs for Math::IntervalOverlap
};

#endif