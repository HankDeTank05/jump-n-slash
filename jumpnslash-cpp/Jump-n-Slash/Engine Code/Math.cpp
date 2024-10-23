#include "Math.h"

#include "EngineAttorney.h"
#include "CollisionVolume.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

bool Math::Intersect(const CollisionVolume& a, const CollisionVolume& b)
{
	return a.IntersectAccept(b);
}

bool Math::Intersect(const CollisionVolumeBSphere& bs1, const CollisionVolumeBSphere& bs2)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeBSphere& bs, const CollisionVolumeAABB& aabb)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeBSphere& bs, const CollisionVolumeOBB& obb)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeAABB& aabb, const CollisionVolumeBSphere& bs)
{
	bool intersection = false;

	sf::Vector2f clampedPoint = ClampPoint(bs.GetCenter(), aabb.GetMin(), aabb.GetMax());

	intersection = PointInSphere(clampedPoint, bs.GetCenter(), bs.GetRadiusSqr());

	return intersection;
}

bool Math::Intersect(const CollisionVolumeAABB& aabb1, const CollisionVolumeAABB& aabb2)
{
	return IntervalOverlap(aabb1.GetMin().x, aabb1.GetMax().x, aabb2.GetMin().x, aabb2.GetMax().x) && // check for overlap on x-axis
		IntervalOverlap(aabb1.GetMin().y, aabb1.GetMax().y, aabb2.GetMin().y, aabb2.GetMax().y); // check for overlap on y-axis
}

bool Math::Intersect(const CollisionVolumeAABB& aabb, const CollisionVolumeOBB& obb)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeOBB& obb, const CollisionVolumeBSphere& bs)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeOBB& obb, const CollisionVolumeAABB& aabb)
{
	assert(false);
	return false;
}

bool Math::Intersect(const CollisionVolumeOBB& obb1, const CollisionVolumeOBB& obb2)
{
	assert(false);
	return false;
}

float Math::ClampValue(float valToClamp, float clampMin, float clampMax)
{
	if (valToClamp < clampMin)
	{
		return clampMin;
	}
	else if (clampMax < valToClamp)
	{
		return clampMax;
	}
	else
	{
		return valToClamp;
	}
}

sf::Vector2f Math::ClampPoint(sf::Vector2f toClamp, sf::Vector2f clampMin, sf::Vector2f clampMax)
{
	sf::Vector2f clampedPoint;

	clampedPoint.x = Math::ClampValue(toClamp.x, clampMin.x, clampMax.x);
	clampedPoint.y = Math::ClampValue(toClamp.y, clampMin.y, clampMax.y);

	return clampedPoint;
}

sf::Vector2i Math::ConvertWorldToScreenSpace(sf::Vector2f worldSpaceCoords)
{
	return EngineAttorney::GameWindow::GetWindow().mapCoordsToPixel(worldSpaceCoords);
}

sf::Vector2f Math::ConvertScreenToWorldSpace(sf::Vector2i screenSpaceCoords)
{
	return EngineAttorney::GameWindow::GetWindow().mapPixelToCoords(screenSpaceCoords);
}

bool Math::IntervalOverlap(float min0, float max0, float min1, float max1)
{
	assert(min0 <= max0);
	assert(min1 <= max1);

	return (min1 <= min0 && min0 <= max1) || // check if min0 is inside range 1
		(min1 <= max0 && max0 <= max1) || // check if max0 is inside range 1
		(min0 <= min1 && min1 <= max0) || // check if min1 is inside range 0
		(min0 <= max1 && max1 <= max0); // check if max1 is inside range 0
}

bool Math::PointInSphere(const sf::Vector2f& point, const sf::Vector2f& sphereCenter, float sphereRadiusSqr)
{
	return DistanceSqr(sphereCenter, point) <= sphereRadiusSqr;
}

float Math::DistanceSqr(const sf::Vector2f& fromA, const sf::Vector2f& toB)
{
	sf::Vector2f delta = toB - fromA;
	return delta.x * delta.x + delta.y * delta.y;
}
