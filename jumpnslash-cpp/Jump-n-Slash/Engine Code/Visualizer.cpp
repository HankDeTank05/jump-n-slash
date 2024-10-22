#include "Visualizer.h"

#include "FontManager.h"

#include "VizCmdFactory.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandPoint.h"
#include "VisualizerCommandCircle.h"
#include "VisualizerCommandRect.h"
#include "VisualizerCommandSegment.h"
#include "VisualizerCommandText.h"
#include "EngineAttorney.h"

#include "../Game Code/Constants.h"

Visualizer* Visualizer::pInstance = nullptr;

Visualizer::Visualizer()
	: cmdList(),
	pCircle(new sf::CircleShape(1.0f)),
	pRect(new sf::RectangleShape()),
	pText(new sf::Text())
{
	pCircle->setOutlineThickness(1.0f); // set the line thickness, since the default is 0.0f

	pRect->setFillColor(sf::Color(0, 0, 0, 0));
	pRect->setOutlineThickness(1.0f);

	pText->setFont(*FontManager::GetFont("consolas"));
}

Visualizer::~Visualizer()
{
	delete pText;
	delete pRect;
	delete pCircle;
	if (cmdList.size() > 0)
	{
		for (VizCmdList::iterator it = cmdList.begin(); it != cmdList.end(); it++)
		{
			(*it)->Recycle();
		}
	}
}

Visualizer& Visualizer::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new Visualizer();
	}
	return *pInstance;
}

void Visualizer::VisualizePoint(const sf::Vector2f& pos, const sf::Color& color)
{
	Instance().privVisualizePoint(pos, color);
}

void Visualizer::VisualizePoint(float x, float y, const sf::Color& color)
{
	Instance().privVisualizePoint(sf::Vector2f(x, y), color);
}

void Visualizer::VisualizeCircle(const sf::Vector2f& pos, float radius, const sf::Color& color, bool showCenter)
{
	Instance().privVisualizeCircle(pos, radius, color, showCenter);
}

void Visualizer::VisualizeRect(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& color)
{
	Instance().privVisualizeRect(pos, size, color);
}

void Visualizer::VisualizeSegment(const sf::Vector2f& pos0, const sf::Vector2f& pos1, const sf::Color& color, bool visualizeEndpoints)
{
	Instance().privVisualizeSegment(pos0, pos1, color, visualizeEndpoints);
}

void Visualizer::VisualizeText(const sf::String& str, const sf::Vector2f& pos, const sf::Color& color, int sizeInPix)
{
	Instance().privVisualizeText(str, pos, color, sizeInPix);
}

void Visualizer::VisualizeText(const sf::String& str, const sf::Vector2i& pos, const sf::Color& color, int sizeInPix)
{
	Instance().privVisualizeText(str, sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)), color, sizeInPix);
}

void Visualizer::ProcessCommands()
{
	Instance().privProcessCommands();
}

void Visualizer::ShowPoint(sf::Vector2f pos, sf::Color color)
{
	Instance().privShowPoint(pos, color);
}

void Visualizer::ShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Instance().privShowCircle(pos, radius, color, showCenter);
}

void Visualizer::ShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	Instance().privShowRect(pos, size, color);
}

void Visualizer::ShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	Instance().privShowSegment(pos0, pos1, color);
}

void Visualizer::ShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privShowText(str, pos, color, sizeInPix);
}

void Visualizer::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void Visualizer::privVisualizePoint(sf::Vector2f pos, sf::Color color)
{
	cmdList.push_back(VizCmdFactory::GetPointCommand(pos, color));
}

void Visualizer::privVisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	cmdList.push_back(VizCmdFactory::GetCircleCommand(pos, radius, color, showCenter));
}

void Visualizer::privVisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	cmdList.push_back(VizCmdFactory::GetRectCommand(pos, size, color));
}

void Visualizer::privVisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color, bool visualizeEndpoints)
{
	cmdList.push_back(VizCmdFactory::GetSegmentCommand(pos0, pos1, color));
	
	if (visualizeEndpoints)
	{
		// visualize the endpoints of the segment as well
		cmdList.push_back(VizCmdFactory::GetPointCommand(pos0, color));
		cmdList.push_back(VizCmdFactory::GetPointCommand(pos1, color));
	}
}

void Visualizer::privVisualizeText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	cmdList.push_back(VizCmdFactory::GetTextCommand(str, pos, color, sizeInPix));
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

void Visualizer::privShowPoint(sf::Vector2f pos, sf::Color color)
{
	pCircle->setFillColor(color); // but give it a fill color
	pCircle->setRadius(VIZ_POINT_RADIUS);
	pCircle->setOrigin(VIZ_POINT_RADIUS, VIZ_POINT_RADIUS); // set the origin to be the middle of the point
	pCircle->setPosition(pos);
	pCircle->setOutlineColor(color);
	Render(*pCircle);
}

void Visualizer::privShowCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	// draw the circle
	pCircle->setRadius(radius);
	pCircle->setOrigin(radius, radius); // set the origin to be the middle of the circle
	pCircle->setPosition(pos);
	pCircle->setFillColor(sf::Color(0, 0, 0, 0)); // make sure it has no fill color (100% transparent)
	pCircle->setOutlineColor(color);
	Render(*pCircle);

	if (showCenter)
	{
		// draw a dot at the center
		privShowPoint(pos, color);
	}
}

void Visualizer::privShowRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	pRect->setPosition(pos);
	pRect->setSize(size);
	pRect->setFillColor(sf::Color(0, 0, 0, 0)); // make sure it has no fill color (100% transparent)
	pRect->setOutlineColor(color);
	Render(*pRect);
}

void Visualizer::privShowSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	sf::Vertex line[] = {
		sf::Vertex(pos0),
		sf::Vertex(pos1)
	};

	line[0].color = color;
	line[1].color = color;

	Render(line, 2);
}

void Visualizer::privShowText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	pText->setString(str);
	pText->setPosition(pos);
	pText->setFillColor(color);
	pText->setCharacterSize(sizeInPix);

	Render(*pText);
}
