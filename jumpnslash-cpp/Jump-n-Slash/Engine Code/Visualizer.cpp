#include "Visualizer.h"

#include "VizCmdFactory.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandCircle.h"

#include "../Game Code/Constants.h"

Visualizer* Visualizer::pInstance = nullptr;

Visualizer::Visualizer()
	: cmdList(),
	pCircle(new sf::CircleShape(1.0f)),
	pRect(new sf::RectangleShape())
{
	pCircle->setOutlineThickness(1.0f); // set the line thickness, since the default is 0.0f

	pRect->setFillColor(sf::Color(0, 0, 0, 0));
	pRect->setOutlineThickness(1.0f);
}

Visualizer::~Visualizer()
{
	delete pRect;
	delete pCircle;
}

Visualizer& Visualizer::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new Visualizer();
	}
	return *pInstance;
}

void Visualizer::VisualizePoint(sf::Vector2f pos, sf::Color color)
{
	Instance().privVisualizePoint(pos, color);
}

void Visualizer::VisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Instance().privVisualizeCircle(pos, radius, color, showCenter);
}

void Visualizer::ProcessCommands()
{
	Instance().privProcessCommands();
}

void Visualizer::ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Instance().privShowCircle(pos, radius, color, showCenter);
}

void Visualizer::ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	Instance().privShowRect(pos, size, color);
}

void Visualizer::privVisualizePoint(sf::Vector2f pos, sf::Color color)
{
	assert(false); // TODO: empty function Visualizer::privVisualizePoint
}

void Visualizer::privVisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	cmdList.push_back(VizCmdFactory::GetCircleCommand(pos, radius, color, showCenter));
}

void Visualizer::privProcessCommands()
{
	for (VizCmdList::iterator it = cmdList.begin(); it != cmdList.end(); it++)
	{
		(*it)->Execute();
		(*it)->Recycle();
	}
	cmdList.clear();
}

void Visualizer::privShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	// draw the circle
	pCircle->setFillColor(sf::Color(0, 0, 0, 0)); // make sure it has no fill color (100% transparent)
	pCircle->setRadius(radius);
	pCircle->setOrigin(radius, radius); // set the origin to be the middle of the circle
	pCircle->setPosition(pos);
	pCircle->setOutlineColor(color);
	Render(*pCircle);

	if (showCenter)
	{
		// draw a dot at the center
		privShowPoint(pos, color);
	}
}

void Visualizer::privShowPoint(sf::Vector2f pos, sf::Color color)
{
	pCircle->setFillColor(color); // but give it a fill color for the center point
	pCircle->setRadius(VIZ_POINT_RADIUS);
	pCircle->setOrigin(VIZ_POINT_RADIUS, VIZ_POINT_RADIUS); // set the origin to be the middle of the point
	pCircle->setPosition(pos);
	pCircle->setOutlineColor(color);
	Render(*pCircle);
}

void Visualizer::privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	assert(false);
}
