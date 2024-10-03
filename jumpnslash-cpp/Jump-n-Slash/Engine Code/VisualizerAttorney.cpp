#include "VisualizerAttorney.h"

#include "Visualizer.h"

void VisualizerAttorney::Circle::ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Visualizer::ShowCircle(pos, radius, color, showCenter);
}

void VisualizerAttorney::Draw::ProcessCommands()
{
	Visualizer::ProcessCommands();
}
