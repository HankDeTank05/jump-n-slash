#ifndef MATH_H
#define MATH_H

#include <SFML/System/Vector2.hpp>

class Math
{
public:
	static float ClampValue(float valToClamp, float clampMin, float clampMax); // TODO: docs for Math::ClampValue
	static sf::Vector2f ClampPoint(sf::Vector2f toClamp, sf::Vector2f clampMin, sf::Vector2f clampMax); // TODO: docs for Math::ClampPoint
	static sf::Vector2i ConvertWorldToScreenSpace(sf::Vector2f worldSpaceCoords);
	static sf::Vector2f ConvertScreenToWorldSpace(sf::Vector2i screenSpaceCoords);
};

#endif