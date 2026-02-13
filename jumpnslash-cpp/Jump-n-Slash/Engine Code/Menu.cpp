#include "Menu.h"

// engine includes
#include "Math.h"
#include "MenuManager.h"
#include "MenuCommand.h"

Menu::Menu(MenuManager* _pMgr, const sf::Text& _menuTitle, const sf::Vector2f& _firstBoxPos, float _boxVertSpacing, const sf::Vector2f& _textOffsetInBox,
	const sf::Color& _baseColor, const sf::Color& _highlightColor,
	const sf::Color& _textColorBase, const sf::Color& _textColorHighlight,
	int _selected)
	: pMgr(_pMgr),
	menuTitle(_menuTitle),
	firstBoxPos(_firstBoxPos),
	boxVertSpacing(_boxVertSpacing),
	textOffsetInBox(_textOffsetInBox),
	boxColorBase(_baseColor),
	boxColorHighlight(_highlightColor),
	boxColors(),
	textColorBase(_textColorBase),
	textColorHighlight(_textColorHighlight),
	menuOptions(),
	menuOptionBox(),
	setMenuOptionBox(false),
	boxPositions(),
	selected(_selected),
	setMenuOptionsList(false)
{
	// do nothing
}

Menu::~Menu()
{
	for (MenuOptionList::iterator it = menuOptions.begin(); it != menuOptions.end(); it++)
	{
		delete it->second;
	}
}

void Menu::Draw()
{
	assert(setMenuOptionBox == true); // did you forget to call SetMenuOptionBox() in the constructor?
	assert(setMenuOptionsList == true); // did you forget to call AddMenuOption() at least once in the constructor?

	// draw menu title

	// draw menu boxes + text
	for (int i = 0; i < menuOptions.size(); i++)
	{
		menuOptionBox.setPosition(boxPositions[i]);
		menuOptionBox.setFillColor(boxColors[i]);

		menuOptions[i].first.setPosition(boxPositions[i] + textOffsetInBox);

		Render(menuOptionBox);
		Render(menuOptions[i].first);
	}
}

void Menu::Update(float deltaTime)
{
	assert(setMenuOptionBox == true); // did you forget to call SetMenuOptionBox() in your Menu-derived class constructor?
	assert(setMenuOptionsList == true); // did you forget to call AddMenuOption() at least once in your Menu-derived class constructor?

	// TODO: move code here instead of in the input processing functions
}

void Menu::MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta)
{
	// TODO: move all of the logic for this into the update function

	// check if mouse cursor is in any of the menu option boxes
	for (int i = 0; i < boxPositions.size(); i++)
	{
		if (Math::PointInRect(pos, boxPositions[i], menuOptionBox.getSize()) == true)
		{
			boxColors[i] = boxColorHighlight;
			menuOptions[i].first.setFillColor(textColorHighlight);
			selected = i;
		}
		else
		{
			boxColors[i] = boxColorBase;
			menuOptions[i].first.setFillColor(textColorBase);
		}
	}
}

void Menu::MouseBtnPressed(sf::Mouse::Button btn)
{
	assert(0 <= selected);
	assert(selected < menuOptions.size());

	menuOptions[selected].second->Execute();
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

	// set the box color
	boxColors.push_back(boxColorBase);

	setMenuOptionsList = true;
}

void Menu::EnterSubmenu(Menu* pSubmenu)
{
	pMgr->EnterSubmenu(pSubmenu);
}

void Menu::ReturnToPrevMenu()
{
	pMgr->ReturnToPrevMenu();
}

void Menu::Init()
{
	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestMouseCursorRegistration();
	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress); // TODO: this will change with the strategy
}

void Menu::End()
{
	RequestUpdateDeregistration();
	RequestDrawDeregistration();
	RequestMouseCursorDeregistration();
	RequestMouseBtnDeregistration(sf::Mouse::Left, MouseEvent::BtnPress); // TODO: this will change with the strategy
}
