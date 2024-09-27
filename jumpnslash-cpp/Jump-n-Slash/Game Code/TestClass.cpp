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

	EnqueueForUpdateRegistration();
	EnqueueForDrawRegistration();

	EnqueueForKeyRegistration(sf::Keyboard::O, KeyEvent::KeyPress);
	EnqueueForKeyRegistration(sf::Keyboard::X, KeyEvent::KeyPress);
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
	//	EnqueueForUpdateDeregistration();
	//	EnqueueForDrawDeregistration();
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
		EnqueueForKeyRegistration(sf::Keyboard::R, KeyEvent::KeyPress);
		EnqueueForKeyRegistration(sf::Keyboard::R, KeyEvent::KeyRelease);
		EnqueueForKeyRegistration(sf::Keyboard::G, KeyEvent::KeyPress);
		EnqueueForKeyRegistration(sf::Keyboard::G, KeyEvent::KeyRelease);
		EnqueueForKeyRegistration(sf::Keyboard::B, KeyEvent::KeyPress);
		EnqueueForKeyRegistration(sf::Keyboard::B, KeyEvent::KeyRelease);
		EnqueueForMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
		EnqueueForMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnRelease);
		EnqueueForMouseBtnRegistration(sf::Mouse::Middle, MouseEvent::BtnPress);
		EnqueueForMouseBtnRegistration(sf::Mouse::Middle, MouseEvent::BtnRelease);
		EnqueueForMouseBtnRegistration(sf::Mouse::Right, MouseEvent::BtnPress);
		EnqueueForMouseBtnRegistration(sf::Mouse::Right, MouseEvent::BtnRelease);
		EnqueueForMouseCursorRegistration();
		circle.setOutlineThickness(10.0f);
		break;
	case sf::Keyboard::X:
		EnqueueForKeyDeregistration(sf::Keyboard::R, KeyEvent::KeyPress);
		EnqueueForKeyDeregistration(sf::Keyboard::R, KeyEvent::KeyRelease);
		EnqueueForKeyDeregistration(sf::Keyboard::G, KeyEvent::KeyPress);
		EnqueueForKeyDeregistration(sf::Keyboard::G, KeyEvent::KeyRelease);
		EnqueueForKeyDeregistration(sf::Keyboard::B, KeyEvent::KeyPress);
		EnqueueForKeyDeregistration(sf::Keyboard::B, KeyEvent::KeyRelease);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnPress);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnRelease);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Middle, MouseEvent::BtnPress);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Middle, MouseEvent::BtnRelease);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Right, MouseEvent::BtnPress);
		EnqueueForMouseBtnDeregistration(sf::Mouse::Right, MouseEvent::BtnRelease);
		EnqueueForMouseCursorDeregistration();
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
