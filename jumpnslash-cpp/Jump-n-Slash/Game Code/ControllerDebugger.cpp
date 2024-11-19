#include "ControllerDebugger.h"

// library includes
#include <SFML/Window/Joystick.hpp>

// engine includes
#include "../Engine Code/Visualizer.h"

ControllerDebugger* ControllerDebugger::pInstance = nullptr;

ControllerDebugger& ControllerDebugger::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new ControllerDebugger();
	}
	return *pInstance;
}

void ControllerDebugger::DisplayDebugInfo()
{
	Instance().privDisplayDebugInfo();
}

void ControllerDebugger::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void ControllerDebugger::privDisplayDebugInfo()
{
	const float INPUT_LINE_SPACING = 50.f;
	const float BTN_START_X = 100.f;
	const float BTN_RECT_SIZE = 20.f;
	const float BTN_RECT_SPACING = 10.f;
	const float AXIS_START_X = 20.f;
	const float LINE_SIZE = BTN_RECT_SIZE;
	const float LINE_HALF = LINE_SIZE / 2.f;
	const float AXIS_SPACING = 10.f;
	for (int c = 0; c < 8; c++)
	{
		float axisLineSize = 10.f;
		if (sf::Joystick::isConnected(c))
		{
			// visualize the name of the controller

			Visualizer::VisualizeText(sf::Joystick::getIdentification(c).name, sf::Vector2f(0.f, (c + 1) * (BTN_RECT_SIZE + INPUT_LINE_SPACING) - BTN_RECT_SIZE));
			
			// visualize the controller index

			Visualizer::VisualizeText(std::to_string(c), sf::Vector2f(0.f, (c + 1) * (BTN_RECT_SIZE + INPUT_LINE_SPACING)));

			// visualize the available axes

			std::vector<bool> availableAxes;
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::X));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::Y));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::Z));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::R));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::U));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::V));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::PovX));
			availableAxes.push_back(sf::Joystick::hasAxis(c, sf::Joystick::Axis::PovY));
			std::vector<std::string> axisNames;
			axisNames.push_back("x");
			axisNames.push_back("y");
			axisNames.push_back("z");
			axisNames.push_back("r");
			axisNames.push_back("u");
			axisNames.push_back("v");
			axisNames.push_back("povX");
			axisNames.push_back("povY");
			std::vector<sf::Joystick::Axis> axes;
			axes.push_back(sf::Joystick::Axis::X);
			axes.push_back(sf::Joystick::Axis::Y);
			axes.push_back(sf::Joystick::Axis::Z);
			axes.push_back(sf::Joystick::Axis::R);
			axes.push_back(sf::Joystick::Axis::U);
			axes.push_back(sf::Joystick::Axis::V);
			axes.push_back(sf::Joystick::Axis::PovX);
			axes.push_back(sf::Joystick::Axis::PovY);
			assert(availableAxes.size() == axisNames.size());
			assert(axisNames.size() == axes.size());

			for (int a = 0; a < axisNames.size(); a++)
			{
				if (availableAxes[a] == true)
				{
					sf::Vector2f pos0(AXIS_START_X + (a * AXIS_SPACING), (c + 1) * (LINE_SIZE + INPUT_LINE_SPACING));
					sf::Vector2f pos1(AXIS_START_X + (a * AXIS_SPACING), (c + 1) * (LINE_SIZE + INPUT_LINE_SPACING) + LINE_SIZE);
					sf::Vector2f pointPos(AXIS_START_X + (a * AXIS_SPACING),
						(c + 1) * (LINE_SIZE + INPUT_LINE_SPACING) + ((sf::Joystick::getAxisPosition(c, axes[a]) / 100.f) * LINE_HALF) + LINE_HALF);
					Visualizer::VisualizeSegment(pos0, pos1);
					Visualizer::VisualizePoint(pointPos);
					Visualizer::VisualizeText(axisNames[a], pos1 + sf::Vector2f(-5.f, 0.f));
				}
			}

			// visualize the available buttons

			unsigned int btnCount = sf::Joystick::getButtonCount(c);
			for (int b = 0; b < btnCount; b++)
			{
				sf::Color color = sf::Joystick::isButtonPressed(c, b) ? sf::Color::Green : sf::Color::Red;
				sf::Vector2f pos(BTN_START_X + b * (BTN_RECT_SIZE + BTN_RECT_SPACING), (c + 1) * (BTN_RECT_SIZE + INPUT_LINE_SPACING));
				sf::Vector2f size(BTN_RECT_SIZE, BTN_RECT_SIZE);
				Visualizer::VisualizeRect(pos, size, color);
				Visualizer::VisualizeText(std::to_string(b), pos, color);
			}
		}
	}
}
