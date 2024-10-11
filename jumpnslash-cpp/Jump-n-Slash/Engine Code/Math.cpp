#include "Math.h"

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
