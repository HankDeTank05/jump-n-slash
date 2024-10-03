#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <list>

#include "../Game Code/Constants.h"

// forward declarations
class VisualizerCommand;

class Visualizer // this class is written as a singleton
{
private:
	static Visualizer* pInstance;

	Visualizer() = default;
	Visualizer(const Visualizer& v) = delete;
	Visualizer& operator=(const Visualizer& v) = delete;
	virtual ~Visualizer() = default;

	static Visualizer& Instance();

	using VizCmdList = std::list<VisualizerCommand*>;

public: // public api functions


private: // engine-only api functions
	static void ShowCircle(sf::Vector2f pos, float radius, sf::Color color = VIZ_DEFAULT_COLOR);
	static void ShowCircle(float x, float y, float radius, sf::Color color = VIZ_DEFAULT_COLOR);

	static void ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color = VIZ_DEFAULT_COLOR);
	static void ShowRect(float x, float y, float width, float height, sf::Color color = VIZ_DEFAULT_COLOR);

	static void ShowLine(sf::Vector2f pos0, sf::Vector2f pos1, float size = VIZ_DEFAULT_LINE_SIZE, sf::Color color = VIZ_DEFAULT_COLOR);
	static void ShowLine(float x0, float y0, float x1, float y1, float size = VIZ_DEFAULT_LINE_SIZE, sf::Color color = VIZ_DEFAULT_COLOR);
	
	// TODO: add text visualization

	static void Terminate();

private: // private api backend functions

	void privShowCircle(sf::Vector2f pos, float radius, sf::Color color);
	void privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);

private: // member variables
	sf::CircleShape* pCircle;
	sf::RectangleShape* pRect;
};

#endif