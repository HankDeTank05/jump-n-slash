#include "TestClass.h"

// engine includes
#include "../Engine Code/JumpSlashEngine.h"
#include "../Engine Code/Visualizer.h"

// game includes
#include "Constants.h"
#include "GameDebugFlags.h"

TestClass::TestClass()
	: circle(64.0f),
	currentFrames(0),
	maxFrames(100)
{
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Red);

	RequestUpdateRegistration();
	RequestDrawRegistration();

	//RequestKeyRegistration(sf::Keyboard::O, KeyEvent::KeyPress);
	//RequestKeyRegistration(sf::Keyboard::X, KeyEvent::KeyPress);
}

TestClass::~TestClass()
{
	// do destructor stuff here
}

void TestClass::Update(float deltaTime)
{
	//currentFrames++;
	//if (currentFrames >= maxFrames)
	//{
	//	RequestUpdateDeregistration();
	//	RequestDrawDeregistration();
	//}

	if (DEBUG_CONTROLLER_INPUT)
	{
		const float INPUT_LINE_SPACING = 10.f;
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

				int btnCount = static_cast<int>(sf::Joystick::getButtonCount(c));
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
}

void TestClass::Draw()
{
	//Render(circle);
}

void TestClass::KeyPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::R:
		circle.setFillColor(sf::Color::Red);
		break;
	case sf::Keyboard::G:
		circle.setFillColor(sf::Color::Green);
		break;
	case sf::Keyboard::B:
		circle.setFillColor(sf::Color::Blue);
		break;
	case sf::Keyboard::O:
		RequestKeyRegistration(sf::Keyboard::R, KeyEvent::KeyPress);
		RequestKeyRegistration(sf::Keyboard::R, KeyEvent::KeyRelease);
		RequestKeyRegistration(sf::Keyboard::G, KeyEvent::KeyPress);
		RequestKeyRegistration(sf::Keyboard::G, KeyEvent::KeyRelease);
		RequestKeyRegistration(sf::Keyboard::B, KeyEvent::KeyPress);
		RequestKeyRegistration(sf::Keyboard::B, KeyEvent::KeyRelease);
		RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
		RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnRelease);
		RequestMouseBtnRegistration(sf::Mouse::Middle, MouseEvent::BtnPress);
		RequestMouseBtnRegistration(sf::Mouse::Middle, MouseEvent::BtnRelease);
		RequestMouseBtnRegistration(sf::Mouse::Right, MouseEvent::BtnPress);
		RequestMouseBtnRegistration(sf::Mouse::Right, MouseEvent::BtnRelease);
		RequestMouseCursorRegistration();
		circle.setOutlineThickness(10.0f);
		break;
	case sf::Keyboard::X:
		RequestKeyDeregistration(sf::Keyboard::R, KeyEvent::KeyPress);
		RequestKeyDeregistration(sf::Keyboard::R, KeyEvent::KeyRelease);
		RequestKeyDeregistration(sf::Keyboard::G, KeyEvent::KeyPress);
		RequestKeyDeregistration(sf::Keyboard::G, KeyEvent::KeyRelease);
		RequestKeyDeregistration(sf::Keyboard::B, KeyEvent::KeyPress);
		RequestKeyDeregistration(sf::Keyboard::B, KeyEvent::KeyRelease);
		RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnPress);
		RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnRelease);
		RequestMouseBtnDeregistration(sf::Mouse::Middle, MouseEvent::BtnPress);
		RequestMouseBtnDeregistration(sf::Mouse::Middle, MouseEvent::BtnRelease);
		RequestMouseBtnDeregistration(sf::Mouse::Right, MouseEvent::BtnPress);
		RequestMouseBtnDeregistration(sf::Mouse::Right, MouseEvent::BtnRelease);
		RequestMouseCursorDeregistration();
		circle.setOutlineThickness(0.0f);
		break;
	}
}

void TestClass::KeyReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::R:
	case sf::Keyboard::G:
	case sf::Keyboard::B:
		circle.setFillColor(sf::Color::White);
		break;
	}
}

void TestClass::MouseBtnPressed(sf::Mouse::Button btn)
{
	switch (btn)
	{
	case sf::Mouse::Left:
		circle.setFillColor(sf::Color::Cyan);
		break;
	case sf::Mouse::Middle:
		circle.setFillColor(sf::Color::Magenta);
		break;
	case sf::Mouse::Right:
		circle.setFillColor(sf::Color::Yellow);
		break;
	}
}

void TestClass::MouseBtnReleased(sf::Mouse::Button btn)
{
	switch (btn)
	{
	case sf::Mouse::Left:
	case sf::Mouse::Middle:
	case sf::Mouse::Right:
		circle.setFillColor(sf::Color::White);
		break;
	}
}

void TestClass::MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta)
{
	if (0 <= pos.x && pos.x < WINDOW_WIDTH && 0 <= pos.y && pos.y < WINDOW_HEIGHT)
	{
		circle.setOutlineColor(sf::Color::Green);
	}
	else
	{
		circle.setOutlineColor(sf::Color::Red);
	}
}
