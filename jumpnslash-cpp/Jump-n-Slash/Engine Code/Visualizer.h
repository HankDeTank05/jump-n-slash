#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <list>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "DrawObject.h"

#include "../Game Code/Constants.h"

// forward declarations
class VisualizerCommand;

class Visualizer : public DrawObject // this class is written as a singleton
{
private:
	static Visualizer* pInstance;

	Visualizer();
	Visualizer(const Visualizer& v) = delete;
	Visualizer& operator=(const Visualizer& v) = delete;
	virtual ~Visualizer();

	static Visualizer& Instance();

	using VizCmdList = std::list<VisualizerCommand*>;

public: // public api functions
	static void VisualizePoint(sf::Vector2f pos, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizePoint

	static void VisualizeCircle(sf::Vector2f pos, float radius, sf::Color color = VIZ_DEFAULT_COLOR, bool showCenter = true); // TODO: docs for Visualizer::VisualizeCircle
	static void VisualizeCircle(float x, float y, float radius, sf::Color color = VIZ_DEFAULT_COLOR, bool showCenter = true); // TODO: docs for Visualizer::VisualizeCircle

	static void VisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeRect
	static void VisualizeRect(float x, float y, sf::Vector2f size, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeRect
	static void VisualizeRect(sf::Vector2f pos, float width, float height, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeRect
	static void VisualizeRect(float x, float y, float width, float height, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeRect
	
	static void VisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeSegment
	static void VisualizeSegment(float x0, float y0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeSegment
	static void VisualizeSegment(sf::Vector2f pos0, float x1, float y1, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeSegment
	static void VisualizeSegment(float x0, float y0, float x1, float y1, sf::Color color = VIZ_DEFAULT_COLOR); // TODO: docs for Visualizer::VisualizeSegment

	static void VisualizeRay(sf::Vector2f pos, sf::Vector2f dir, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeRay(float x, float y, sf::Vector2f dir, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeRay(sf::Vector2f pos, float dirX, float dirY, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeRay(float x, float y, float dirX, float dirY, sf::Color color = VIZ_DEFAULT_COLOR);

	static void VisualizeLine(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeLine(float x0, float y0, sf::Vector2f pos1, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeLine(sf::Vector2f pos0, float x1, float y1, sf::Color color = VIZ_DEFAULT_COLOR);
	static void VisualizeLine(float x0, float y0, float x1, float y1, sf::Color color = VIZ_DEFAULT_COLOR);
	
	static void VisualizeText(sf::Text text, sf::Color color = VIZ_DEFAULT_COLOR, int sizeInPix = 24);

private: // engine-only api functions
	friend class VisualizerAttorney;
	static void ProcessCommands();

	static void ShowPoint(sf::Vector2f pos, sf::Color color);
	static void ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	static void ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	static void ShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);

	static void Terminate();

private: // private api backend functions
	void privVisualizePoint(sf::Vector2f pos, sf::Color color);
	void privVisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	void privVisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privVisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);

	void privProcessCommands();

	void privShowPoint(sf::Vector2f pos, sf::Color color);
	void privShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter);
	void privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color);
	void privShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color);

private: // member variables
	VizCmdList cmdList;
	sf::CircleShape* pCircle;
	sf::RectangleShape* pRect;
};

#endif