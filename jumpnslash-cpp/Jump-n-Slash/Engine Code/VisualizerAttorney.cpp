#include "VisualizerAttorney.h"

#include "Visualizer.h"

void VisualizerAttorney::Draw::ProcessCommands()
{
	Visualizer::ProcessCommands();
}

void VisualizerAttorney::Circle::ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Visualizer::ShowCircle(pos, radius, color, showCenter);
}

void VisualizerAttorney::Point::ShowPoint(sf::Vector2f pos, sf::Color color)
{
	Visualizer::ShowPoint(pos, color);
}

void VisualizerAttorney::Rect::ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	Visualizer::ShowRect(pos, size, color);
}

void VisualizerAttorney::Segment::ShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	Visualizer::ShowSegment(pos0, pos1, color);
}

void VisualizerAttorney::Text::ShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Visualizer::ShowText(str, pos, color, sizeInPix);
}

void VisualizerAttorney::Termination::Terminate()
{
	Visualizer::Terminate();
}
