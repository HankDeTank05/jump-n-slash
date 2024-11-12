#include "PauseMenu.h"

// library includes
#include <SFML/Graphics/Text.hpp>

// engine includes
#include "../Engine Code/FontManager.h"

// game includes
#include "ResumeGameCommand.h"
#include "ChangeControlsCommand.h"
#include "QuitGameCommand.h"
#include "MenuManager.h"

PauseMenu::PauseMenu(MenuManager* pMgr)
	: Menu(pMgr, sf::Text("Pause Menu", *FontManager::GetFont("delfino")), sf::Vector2f(100.f, 100.f), 20.f, sf::Vector2f(10.f, 10.f),
		sf::Color::White, sf::Color::Green,
		sf::Color::Black, sf::Color::Black)
{
	sf::RectangleShape optBox;
	optBox.setSize(sf::Vector2f(300.f, 50.f));
	optBox.setFillColor(sf::Color::White);
	optBox.setOutlineColor(sf::Color::Black);
	optBox.setOutlineThickness(1.f);
	SetMenuOptionBox(optBox);

	AddMenuOption(sf::Text("Resume Game", *FontManager::GetFont("delfino")), new ResumeGameCommand());
	AddMenuOption(sf::Text("Change Controls", *FontManager::GetFont("delfino")), new ChangeControlsCommand(pMgr));
	AddMenuOption(sf::Text("Quit Game", *FontManager::GetFont("delfino")), new QuitGameCommand());
}
