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
	class Point
	{
	private:
		friend class VisualizerCommandPoint;
		static void ShowPoint(sf::Vector2f pos, sf::Color color);
	};
	class Rect
	{
	private:
		friend class VisualizerCommandRect;
		static void ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	};
};

#endif