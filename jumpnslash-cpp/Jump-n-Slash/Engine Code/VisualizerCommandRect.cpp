#include "VisualizerCommandRect.h"

#include "VisualizerAttorney.h"
#include "VizCmdFactory.h"

VisualizerCommandRect::VisualizerCommandRect()
	: pos(),
	size()
{
	// do nothing
}

VisualizerCommandRect::~VisualizerCommandRect()
{
	// do nothing
}

void VisualizerCommandRect::Init(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	this->pos = pos;
	this->size = size;
	this->color = color;
}

void VisualizerCommandRect::Execute()
{
	VisualizerAttorney::Rect::ShowRect(pos, size, color);
}

void VisualizerCommandRect::Recycle()
{
	VizCmdFactory::RecycleRectCommand(this);
}
