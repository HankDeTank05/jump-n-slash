#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <SFML/Graphics.hpp>
#include "../Engine Code/UpdatableObject.h"
#include "../Engine Code/DrawableObject.h"
#include "../Engine Code/InputObject.h"

class TestClass : public UpdatableObject, public DrawableObject, public InputObject
{
public:
	TestClass();
	TestClass(const TestClass& p) = delete;
	TestClass& operator=(const TestClass& p) = delete;
	virtual ~TestClass();

	virtual void Update() override;
	virtual void Draw() override;
	virtual void KeyPressed(sf::Keyboard::Key key) override;
	virtual void KeyReleased(sf::Keyboard::Key key) override;
	virtual void MouseBtnPressed(sf::Mouse::Button btn) override;
	virtual void MouseBtnReleased(sf::Mouse::Button btn) override;

	
private:
	sf::CircleShape circle;
	int currentFrames;
	int maxFrames;
};

#endif