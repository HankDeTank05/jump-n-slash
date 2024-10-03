#include "Visualizer.h"

Visualizer* Visualizer::pInstance = nullptr;

Visualizer& Visualizer::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new Visualizer();
	}
	return *pInstance;
}

void Visualizer::ShowCircle(sf::Vector2f pos, float radius, sf::Color color)
{
	Instance().privShowCircle(pos, radius, color);
}

void Visualizer::ShowCircle(float x, float y, float radius, sf::Color color)
{
	Instance().privShowCircle(sf::Vector2f(x, y), radius, color);
}

void Visualizer::ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	Instance().privShowRect(pos, size, color);
}

void Visualizer::ShowRect(float x, float y, float width, float height, sf::Color color)
{
	Instance().privShowRect(sf::Vector2f(x, y), sf::Vector2f(width, height), color);
}

void Visualizer::privShowCircle(sf::Vector2f pos, float radius, sf::Color color)
{
	assert(false);
}

void Visualizer::privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	assert(false);
}
