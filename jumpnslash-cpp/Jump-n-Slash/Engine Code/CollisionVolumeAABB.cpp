#include "CollisionVolumeAABB.h"

#include "Math.h"
#include "Visualizer.h"
#include "ConvenienceFunctions.h"

#include "../Game Code/DebugFlags.h"

CollisionVolumeAABB::CollisionVolumeAABB(const sf::Vector2f& min, const sf::Vector2f& max)
	: CollisionVolumeBoundingBox(sf::Transform(), min, max)
{
	// do nothing
}

const sf::Vector2f& CollisionVolumeAABB::GetMin() const
{
	return min;
}

const sf::Vector2f& CollisionVolumeAABB::GetMax() const
{
	return max;
}

void CollisionVolumeAABB::ComputeData(sf::Sprite* pSprite, const sf::Transform& _tform)
{
	// do some obb stuff
	
	tform = _tform;

	// adjust the aabb

	sf::FloatRect aabb = pSprite->getGlobalBounds();
	min = aabb.getPosition();
	max = min + aabb.getSize();

	// do some more obb stuff

	halfDiag = (max - min) * 0.5f;
	worldSpaceCenter = min + halfDiag;
	const float* mat = tform.getMatrix();
	scaleFactorSqr = mat[0] * mat[0] + mat[1] * mat[1] + mat[2] * mat[2] + mat[3] * mat[3];
	// TODO: make sure ^this^ is doing what you think it is
	// got this info from: https://stackoverflow.com/questions/17717600/confusion-between-c-and-opengl-matrix-order-row-major-vs-column-major
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return Math::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return Math::Intersect(*this, other);
}

void CollisionVolumeAABB::DebugView(const sf::Color& color) const
{
	// visualize aabb
	Visualizer::VisualizeRect(min, max - min, color);

	// visualize min point and coords
	Visualizer::VisualizePoint(min, color);
	if (DEBUG_COLLISION_SHOW_NUMBERS) Visualizer::VisualizeText(Convenience::ConvertToString(min), min, color);

	// visualize max point and coords
	Visualizer::VisualizePoint(max, color);
	if (DEBUG_COLLISION_SHOW_NUMBERS) Visualizer::VisualizeText(Convenience::ConvertToString(max), max, color);
}
