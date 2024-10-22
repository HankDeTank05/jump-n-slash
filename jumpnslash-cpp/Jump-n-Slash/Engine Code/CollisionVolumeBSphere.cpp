#include "CollisionVolumeBSphere.h"

#include "Visualizer.h"

void CollisionVolumeBSphere::DebugView(const sf::Color& color) const
{
	Visualizer::VisualizeCircle(center, radius, color, false);
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
