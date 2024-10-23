#include "ConvenienceFunctions.h"

std::string Convenience::ConvertToString(float num)
{
	return std::to_string(num);
}

std::string Convenience::ConvertToString(int num)
{
	return std::to_string(num);
}

std::string Convenience::ConvertToString(bool flag)
{
	if (flag == true)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

std::string Convenience::ConvertToString(sf::Vector2f vect)
{
	return "(" + ConvertToString(vect.x) + ", " + ConvertToString(vect.y) + ")";
}

std::string Convenience::ConvertToString(sf::Vector2i vect)
{
	return "(" + ConvertToString(vect.x) + ", " + ConvertToString(vect.y) + ")";
}
