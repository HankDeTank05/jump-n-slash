#ifndef VISUALIZER_ATTORNEY_H
#define VISUALIZER_ATTORNEY_H

#include <SFML/Graphics.hpp>

class VisualizerAttorney
{
public:
	class Draw
	{
	private:
		friend class DrawManager;
		static void ProcessCommands();
	};
	class Circle
	{
	private:
		friend class VisualizerCommandCircle;
		static void ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	};
};

#endif