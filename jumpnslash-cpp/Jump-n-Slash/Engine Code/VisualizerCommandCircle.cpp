#include "VisualizerCommandCircle.h"

VisualizerCommandCircle::VisualizerCommandCircle()
	: pos(),
	radius()
{
	// do nothing
}

VisualizerCommandCircle::~VisualizerCommandCircle()
{
	// do nothing
}

void VisualizerCommandCircle::Init(sf::Vector2f pos, float radius, sf::Color color)
{
	this->pos = pos;
	this->radius = radius;
	this->color = color;
}
