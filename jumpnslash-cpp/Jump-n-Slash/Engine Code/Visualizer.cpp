#include "Visualizer.h"

#include "FontManager.h"

#include "VizCmdFactory.h"
#include "VisualizerCommand.h"
#include "VisualizerCommandPoint.h"
#include "VisualizerCommandCircle.h"
#include "VisualizerCommandRect.h"
#include "VisualizerCommandSegment.h"
#include "VisualizerCommandText.h"

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

void Visualizer::VisualizePoint(sf::Vector2f pos, sf::Color color)
{
	Instance().privVisualizePoint(pos, color);
}

void Visualizer::VisualizePoint(float x, float y, sf::Color color)
{
	Instance().privVisualizePoint(sf::Vector2f(x, y), color);
}

void Visualizer::VisualizeCircle(sf::Vector2f pos, float radius, sf::Color color, bool showCenter)
{
	Instance().privVisualizeCircle(pos, radius, color, showCenter);
}

void Visualizer::VisualizeCircle(float x, float y, float radius, sf::Color color, bool showCenter)
{
	Instance().privVisualizeCircle(sf::Vector2f(x, y), radius, color, showCenter);
}

void Visualizer::VisualizeRect(sf::Vector2f pos, sf::Vector2f size, sf::Color color)
{
	Instance().privVisualizeRect(pos, size, color);
}

void Visualizer::VisualizeRect(float x, float y, sf::Vector2f size, sf::Color color)
{
	Instance().privVisualizeRect(sf::Vector2f(x, y), size, color);
}

void Visualizer::VisualizeRect(sf::Vector2f pos, float width, float height, sf::Color color)
{
	Instance().privVisualizeRect(pos, sf::Vector2f(width, height), color);
}

void Visualizer::VisualizeRect(float x, float y, float width, float height, sf::Color color)
{
	Instance().privVisualizeRect(sf::Vector2f(x, y), sf::Vector2f(width, height), color);
}

void Visualizer::VisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	Instance().privVisualizeSegment(pos0, pos1, color);
}

void Visualizer::VisualizeSegment(float x0, float y0, sf::Vector2f pos1, sf::Color color)
{
	Instance().privVisualizeSegment(sf::Vector2f(x0, y0), pos1, color);
}

void Visualizer::VisualizeSegment(sf::Vector2f pos0, float x1, float y1, sf::Color color)
{
	Instance().privVisualizeSegment(pos0, sf::Vector2f(x1, y1), color);
}

void Visualizer::VisualizeSegment(float x0, float y0, float x1, float y1, sf::Color color)
{
	Instance().privVisualizeSegment(sf::Vector2f(x0, y0), sf::Vector2f(x1, y1), color);
}

void Visualizer::VisualizeText(sf::String str, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privVisualizeText(str, pos, color, sizeInPix);
}

void Visualizer::VisualizeText(sf::Vector2f vect, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privVisualizeText("(" + std::to_string(vect.x) + ", " + std::to_string(vect.y) + ")", pos, color, sizeInPix);
}

void Visualizer::VisualizeText(sf::Vector2i vect, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privVisualizeText("(" + std::to_string(vect.x) + ", " + std::to_string(vect.y) + ")", pos, color, sizeInPix);
}

void Visualizer::VisualizeText(int num, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privVisualizeText(std::to_string(num), pos, color, sizeInPix);
}

void Visualizer::VisualizeText(float num, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	Instance().privVisualizeText(std::to_string(num), pos, color, sizeInPix);
}

void Visualizer::VisualizeText(bool flag, sf::Vector2f pos, sf::Color color, int sizeInPix)
{
	std::string str;
	if (flag == true)
	{
		str = "true";
	}
	else
	{
		str = "false";
	}
	Instance().privVisualizeText(str, pos, color, sizeInPix);
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

void Visualizer::privVisualizeSegment(sf::Vector2f pos0, sf::Vector2f pos1, sf::Color color)
{
	cmdList.push_back(VizCmdFactory::GetSegmentCommand(pos0, pos1, color));
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
