#include "PauseMenu.h"

// library includes
#include <SFML/Graphics/Text.hpp>

// engine includes
#include "../Engine Code/FontManager.h"

PauseMenu::PauseMenu()
	: Menu(sf::Text("Pause Menu", *FontManager::GetFont("delfino")),
		sf::Vector2f(100.f, 100.f),
		20.f,
		sf::Vector2f(10.f, 10.f),
		sf::Color::White,
		sf::Color::Green)
{
	sf::RectangleShape optBox;
	optBox.setSize(sf::Vector2f(300.f, 50.f));
	optBox.setFillColor(sf::Color::White);
	optBox.setOutlineColor(sf::Color::Black);
	optBox.setOutlineThickness(1.f);
	SetMenuOptionBox(optBox);

	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestMouseCursorRegistration();
	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
}
