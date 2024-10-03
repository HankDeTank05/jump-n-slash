#include "VisualizerCommandCircle.h"

#include "VisualizerAttorney.h"
#include "VizCmdFactory.h"

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

void VisualizerCommandCircle::Init(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	this->pos = pos;
	this->radius = radius;
	this->color = color;
	this->showCenter = showCenter;
}

void VisualizerCommandCircle::Execute()
{
	VisualizerAttorney::Circle::ShowCircle(pos, radius, color, showCenter);
}

void VisualizerCommandCircle::Recycle()
{
	VizCmdFactory::RecycleCircleCommand(this);
}
