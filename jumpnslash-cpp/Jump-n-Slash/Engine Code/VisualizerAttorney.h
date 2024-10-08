#ifndef VISUALIZER_ATTORNEY_H
#define VISUALIZER_ATTORNEY_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

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
	class Segment
	{
	private:
		friend class VisualizerCommandSegment;
		static void ShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);
	};
	class Text
	{
	private:
		friend class VisualizerCommandText;
		static void ShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix);
	};
	class Termination
	{
		friend class JumpSlashEngine;
		static void Terminate();
	};
};

#endif