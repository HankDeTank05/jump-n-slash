#include "Menu.h"

// engine includes
#include "../Engine Code/Math.h"

Menu::Menu(const sf::Text& _menuTitle, const sf::Vector2f& _firstBoxPos, float _boxVertSpacing, const sf::Vector2f& _textOffsetInBox,
	const sf::Color& _baseColor, const sf::Color& _highlightColor)
	: menuTitle(_menuTitle),
	firstBoxPos(_firstBoxPos),
	boxVertSpacing(_boxVertSpacing),
	textOffsetInBox(_textOffsetInBox),
	baseColor(_baseColor),
	highlightColor(_highlightColor),
	menuOptionBox(),
	setMenuOptionBox(false),
	menuOptions(),
	boxPositions(),
	selected(-1),
	setMenuOptionsList(false)
{
	// do nothing
}

void Menu::Draw()
{
	assert(setMenuOptionBox == true); // did you forget to call SetMenuOptionBox() in the constructor?
	assert(setMenuOptionsList == true); // did you forget to call AddMenuOption() at least once in the constructor?

	// draw menu title

	// draw menu boxes + text
	int optNum = 0;
	for (MenuOptionList::iterator it = menuOptions.begin(); it != menuOptions.end(); it++)
	{
		// set position of menu option box
		sf::Vector2f drawPos = firstBoxPos + static_cast<float>(optNum) * sf::Vector2f(0.f, boxVertSpacing + menuOptionBox.getSize().y);
		menuOptionBox.setPosition(drawPos);

		// set position of menu option text
		drawPos += textOffsetInBox;
		it->first.setPosition(drawPos);

		Render(menuOptionBox);
		Render(it->first);

		optNum++;
	}
	for (int i = 0; i < menuOptions.size(); i++)
	{
		menuOptionBox.setPosition(boxPositions[i]);
	}
}

void Menu::MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta)
{
	// check if mouse cursor is in any of the menu option boxes
	for (int i = 0; i < boxPositions.size(); i++)
	{
		if (Math::PointInRect(pos, boxPositions[i], menuOptionBox.getSize()) == true)
		{

		}
	}
}

void Menu::SetMenuOptionBox(const sf::RectangleShape& _menuOptionBox)
{
	menuOptionBox = _menuOptionBox;
	setMenuOptionBox = true;
}

void Menu::AddMenuOption(const sf::Text& optionName, MenuCommand* pOptionFunction)
{
	// set the position of the option box
	boxPositions.push_back(firstBoxPos + static_cast<float>(boxPositions.size()) * sf::Vector2f(0.f, boxVertSpacing + menuOptionBox.getSize().y));

	// set the text position and add the option to the list
	menuOptions.push_back(MenuOption(optionName, pOptionFunction));
	menuOptions.at(menuOptions.size() - 1).first.setPosition(boxPositions.at(boxPositions.size() - 1) + textOffsetInBox);

	setMenuOptionsList = true;
}
