#include "ChangeControlsMenu.h"

// engine includes
#include "../Engine Code/FontManager.h"
#include "../Engine Code/ExitSubmenuCommand.h"

ChangeControlsMenu::ChangeControlsMenu(MenuManager* pMgr)
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

	AddMenuOption(sf::Text("Keyboard", *FontManager::GetFont("delfino")), new ExitSubmenuCommand(pMgr)); // TODO: replace this with an ExitSubmenuCommand-derived class
	AddMenuOption(sf::Text("Switch Pro", *FontManager::GetFont("delfino")), new ExitSubmenuCommand(pMgr)); // TODO: replace this with an ExitSubmenuCommand-derived class
	AddMenuOption(sf::Text("DualSense", *FontManager::GetFont("delfino")), new ExitSubmenuCommand(pMgr)); // TODO: replace this with an ExitSubmenuCommand-derived class
	AddMenuOption(sf::Text("Back", *FontManager::GetFont("delfino")), new ExitSubmenuCommand(pMgr));
}
