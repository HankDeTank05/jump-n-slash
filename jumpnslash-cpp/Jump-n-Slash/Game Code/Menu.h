#ifndef MENU_H
#define MENU_H

// language includes
#include <vector>
#include <string>

// library includes
#include <SFML/Graphics/RectangleShape.hpp>

// engine includes
#include "../Engine Code/DrawObject.h"
#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/InputObject.h"

// forward declarations
class MenuCommand;

class Menu : public DrawObject, public UpdateObject, public InputObject
{
public:
	Menu() = delete;
	Menu(const sf::Text& menuTitle, const sf::Vector2f& firstBoxPos, float boxVertSpacing, const sf::Vector2f& textOffsetInBox,
		const sf::Color& baseColor, const sf::Color& highlightColor);
	Menu(const Menu& m) = delete;
	Menu& operator=(const Menu& m) = delete;
	virtual ~Menu() = default;

	using MenuOption = std::pair<sf::Text, MenuCommand*>;
	using MenuOptionList = std::vector<MenuOption>;

	virtual void Draw() override final;

	virtual void MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta) override final;
	virtual void MouseBtnPressed(sf::Mouse::Button btn) override final;

protected:
	void SetMenuOptionBox(const sf::RectangleShape& menuOptionBox);
	void AddMenuOption(const sf::Text& optionName, MenuCommand* pOptionFunction);

private:
	sf::Text menuTitle;
	sf::Vector2f firstBoxPos;
	float boxVertSpacing;
	sf::Vector2f textOffsetInBox;
	sf::Color baseColor;
	sf::Color highlightColor;
	sf::RectangleShape menuOptionBox;
	bool setMenuOptionBox; // flag to prevent running the menu if the menuOptionBox is not set
	MenuOptionList menuOptions;
	std::vector<sf::Vector2f> boxPositions;
	int selected;
	bool setMenuOptionsList; // flag to prevent running the menu if the menuOptions list is not set
};

#endif