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

	// TODO: docs for Math::Intersect(volume, volume)
	static bool Intersect(const CollisionVolume& a, const CollisionVolume& b); // generic collision volume intersection test
	// TODO: docs for intersect bs/bs
	static bool Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2); 
	// TODO: docs for intersect bs/aabb
	static bool Intersect(const CollisionVolumeBSphere& bs, const CollisionVolumeAABB& aabb); 
	// TODO: docs for intersect aabb/bs
	static bool Intersect(const CollisionVolumeAABB& aabb, const CollisionVolumeBSphere& bs); 
	// TODO: docs for intersect aabb/aabb
	static bool Intersect(const CollisionVolumeAABB& aabb1, const CollisionVolumeAABB& aabb2); 
	
	// general math support functions

	// TODO: docs for Math::ClampValue
	static float ClampValue(float valToClamp, float clampMin, float clampMax); 
	// TODO: docs for Math::ClampPoint
	static sf::Vector2f ClampPoint(sf::Vector2f toClamp, sf::Vector2f clampMin, sf::Vector2f clampMax); 
	// TODO: docs for Math::ConvertWorldToScreenSpace
	static sf::Vector2i ConvertWorldToScreenSpace(sf::Vector2f worldSpaceCoords); 
	// TODO: docs for Math::ConvertScreenToWorldSpace
	static sf::Vector2f ConvertScreenToWorldSpace(sf::Vector2i screenSpaceCoords); 
	// TODO: docs for Math::IntervalOverlap
	static bool IntervalOverlap(float min0, float max0, float min1, float max1); 
	// TODO: docs for Math::PointInSphere
	static bool PointInSphere(const sf::Vector2f& point, const sf::Vector2f& sphereCenter, float sphereRadiusSqr); 
	// TODO: docs for Math::PointInRect(v2f, v2f, v2f)
	static bool PointInRect(const sf::Vector2f& point, const sf::Vector2f& rectPos, const sf::Vector2f& rectSize);
	// TODO: docs for Math::PointInRect(v2i, v2f, v2f)
	static bool PointInRect(const sf::Vector2i& point, const sf::Vector2f& rectPos, const sf::Vector2f& rectSize);
	// TODO: docs for Math::DistanceSqr
	static float DistanceSqr(const sf::Vector2f& fromA, const sf::Vector2f& toB); 
	// TODO: docs for Math::Max
	static float Max(float val1, float val2); 
	// TODO: docs for Math::Min
	static float Min(float val1, float val2);
};

#endif