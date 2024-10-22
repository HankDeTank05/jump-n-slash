#include "CollisionVolumeBoundingBox.h"

CollisionVolumeBoundingBox::CollisionVolumeBoundingBox(const sf::Transform& _tform, const sf::Vector2f& _min, const sf::Vector2f& _max)
    : tform(_tform),
    min(_min),
    max(_max),
    halfDiag((max - min) * 0.5f),
    worldSpaceCenter(tform * (min + halfDiag)),
    scaleFactorSqr(tform.getMatrix()[0] * tform.getMatrix()[0] + tform.getMatrix()[1] * tform.getMatrix()[1] +
    tform.getMatrix()[2] * tform.getMatrix()[2] + tform.getMatrix()[3] * tform.getMatrix()[3]) // TODO: make sure this is doing what you think it is. got this info from: https://stackoverflow.com/questions/17717600/confusion-between-c-and-opengl-matrix-order-row-major-vs-column-major
{
    assert(min.x <= max.x);
    assert(min.y <= max.y);
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
