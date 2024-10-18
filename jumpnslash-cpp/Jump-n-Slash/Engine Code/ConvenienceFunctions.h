#ifndef CONVENIENCE_FUNCTIONS_H
#define CONVENIENCE_FUNCTIONS_H

#include <string>

#include <SFML/System/Vector2.hpp>

class Convenience
{
public:
	static std::string ConvertToString(sf::Vector2f vect);
	static std::string ConvertToString(sf::Vector2i vect);
};

#endif