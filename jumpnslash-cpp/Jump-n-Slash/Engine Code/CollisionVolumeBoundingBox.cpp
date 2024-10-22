#include "CollisionVolumeBoundingBox.h"

CollisionVolumeBoundingBox::CollisionVolumeBoundingBox(const sf::Transform& _tform, const sf::Vector2f& _min, const sf::Vector2f& _max)
    : tform(_tform),
    min(_min),
    max(_max)
{
    // do nothing
}

const sf::Transform& CollisionVolumeBoundingBox::GetTransform() const
{
    return tform;
}

const sf::Vector2f& CollisionVolumeBoundingBox::GetMin() const
{
    return max;
}

const sf::Vector2f& CollisionVolumeBoundingBox::GetMax() const
{
    return max;
}

const sf::Vector2f& CollisionVolumeBoundingBox::GetHalfDiagonal() const
{
    return halfDiag;
}

const sf::Vector2f& CollisionVolumeBoundingBox::GetWorldSpaceCenter() const
{
    return worldSpaceCenter;
}

float CollisionVolumeBoundingBox::GetScaleFactorSqr() const
{
    return scaleFactorSqr;
}
