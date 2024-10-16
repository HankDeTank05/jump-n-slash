#include "ConvenienceFunctions.h"

std::string Convenience::ConvertToString(sf::Vector2f vect)
{
	return "(" + std::to_string(vect.x) + ", " + std::to_string(vect.y) + ")";
}

std::string Convenience::ConvertToString(sf::Vector2i vect)
{
	return "(" + std::to_string(vect.x) + ", " + std::to_string(vect.y) + ")";
}
