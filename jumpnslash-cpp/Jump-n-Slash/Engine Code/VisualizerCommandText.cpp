#include "VisualizerCommandText.h"

#include "VisualizerAttorney.h"
#include "VizCmdFactory.h"

void VisualizerCommandText::Init(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	this->str = str;
	this->pos = pos;
	this->color = color;
	this->sizeInPix = sizeInPix;
}

void VisualizerCommandText::Execute()
{
	VisualizerAttorney::Text::ShowText(str, pos, color, sizeInPix);
}

void VisualizerCommandText::Recycle()
{
	VizCmdFactory::RecycleTextCommand(this);
}
