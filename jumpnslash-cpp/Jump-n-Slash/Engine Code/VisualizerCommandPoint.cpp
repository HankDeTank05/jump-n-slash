#include "VisualizerCommandPoint.h"

#include "VisualizerAttorney.h"
#include "VizCmdFactory.h"

VisualizerCommandPoint::VisualizerCommandPoint()
	: pos()
{
	// do nothing
}

VisualizerCommandPoint::~VisualizerCommandPoint()
{
	// do nothing
}

void VisualizerCommandPoint::Init(sf::Vector2f pos, sf::Color color)
{
	this->pos = pos;
	this->color = color;
}

void VisualizerCommandPoint::Execute()
{
	VisualizerAttorney::Point::ShowPoint(pos, color);
}

void VisualizerCommandPoint::Recycle()
{
	VizCmdFactory::RecyclePointCommand(this);
}
