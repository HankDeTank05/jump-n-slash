#include "TestClass.h"

#include "../Engine Code/JumpSlashEngine.h"
#include "Constants.h"

TestClass::TestClass()
	: circle(64.0f),
	currentFrames(0),
	maxFrames(100)
{
	circle.setFillColor(sf::Color::White);
	circle.setOutlineColor(sf::Color::Red);

	RequestUpdateRegistration();
	RequestDrawRegistration();

	RequestKeyRegistration(sf::Keyboard::O, KeyEvent::KeyPress);
	RequestKeyRegistration(sf::Keyboard::X, KeyEvent::KeyPress);
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
}

void TestClass::Draw()
{
	JumpSlashEngine::GetWindow().draw(circle);
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
