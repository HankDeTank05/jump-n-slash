#include "VisualizerCommandSegment.h"

#include "VisualizerAttorney.h"
#include "VizCmdFactory.h"

VisualizerCommandSegment::VisualizerCommandSegment()
	: pos0(),
	pos1()
{
	// do nothing
}

VisualizerCommandSegment::~VisualizerCommandSegment()
{
	// do nothing
}

void VisualizerCommandSegment::Init(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	this->pos0 = pos0;
	this->pos1 = pos1;
	this->color = color;
}

void VisualizerCommandSegment::Execute()
{
	VisualizerAttorney::Segment::ShowSegment(pos0, pos1, color);
}

void VisualizerCommandSegment::Recycle()
{
	VizCmdFactory::RecycleSegmentCommand(this);
}
