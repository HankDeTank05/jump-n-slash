#ifndef MATH_H
#define MATH_H

#include <SFML/System/Vector2.hpp>

class Math
{
public:
	static float ClampValue(float valToClamp, float clampMin, float clampMax);
	static sf::Vector2f ClampPoint(sf::Vector2f toClamp, sf::Vector2f clampMin, sf::Vector2f clampMax);
};

#endif