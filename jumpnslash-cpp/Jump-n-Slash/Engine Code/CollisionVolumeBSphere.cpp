#include "CollisionVolumeBSphere.h"

#include "Visualizer.h"
#include "Math.h"
#include "ConvenienceFunctions.h"

#include "../Game Code/DebugFlags.h"

CollisionVolumeBSphere::CollisionVolumeBSphere(sf::Vector2f _center, float _radius)
	: center(_center),
	radius(_radius)
{
	// do nothing
}

const sf::Vector2f& CollisionVolumeBSphere::GetCenter() const
{
	return center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return radius;
}

float CollisionVolumeBSphere::GetRadiusSqr() const
{
	return radius * radius;
}

void CollisionVolumeBSphere::ComputeData(sf::Sprite* pSprite, const sf::Transform& tform)
{
	sf::Vector2f aabbPos = pSprite->getGlobalBounds().getPosition();
	sf::Vector2f aabbSize = pSprite->getGlobalBounds().getSize();
	center = aabbPos + aabbSize * 0.5f;
	radius = Math::Max(aabbSize.x, aabbSize.y) * 0.5f;
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return Math::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return Math::Intersect(*this, other);
}

void CollisionVolumeBSphere::DebugView(const sf::Color& color) const
{
	// visualize bsphere with center point
	Visualizer::VisualizeCircle(center, radius, color, true);

	// visualize the coords of the center point
	if (DEBUG_COLLISION_SHOW_NUMBERS) Visualizer::VisualizeText(Convenience::ConvertToString(center), center, color);

	// visualize the radius
	sf::Vector2f radiusLineEnd = center + sf::Vector2f(1.f, 0.f) * radius;
	Visualizer::VisualizeSegment(center, radiusLineEnd, color);

	// visualize the length of the radius
	if (DEBUG_COLLISION_SHOW_NUMBERS)
	{
		sf::Vector2f radiusTextDrawPos = center + (sf::Vector2f(0.5f, 0.f) * radius) + sf::Vector2f(0.f, static_cast<float>(-VIZ_DEFAULT_TEXT_SIZE)) * 1.5f;
		Visualizer::VisualizeText(std::to_string(radius), radiusTextDrawPos, color);
	}
}
