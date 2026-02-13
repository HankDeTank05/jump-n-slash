#ifndef MENU_H
#define MENU_H

// language includes
#include <vector>
#include <string>
#include <stack>

// library includes
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

// engine includes
#include "DrawObject.h"
#include "UpdateObject.h"
#include "InputObject.h"

// forward declarations
class MenuManager;
class MenuCommand;

class Menu : public DrawObject, public UpdateObject, public InputObject
{
public:
	Menu() = delete;
	Menu(MenuManager* pMgr, const sf::Text& menuTitle, const sf::Vector2f& firstBoxPos, float boxVertSpacing, const sf::Vector2f& textOffsetInBox,
		const sf::Color& boxColorBase, const sf::Color& boxColorHighlight,
		const sf::Color& textColorBase, const sf::Color& textColorHighlight,
		int selected = -1);
	Menu(const Menu& m) = delete;
	Menu& operator=(const Menu& m) = delete;
	virtual ~Menu();

	using MenuOption = std::pair<sf::Text, MenuCommand*>;
	using MenuOptionList = std::vector<MenuOption>;

	virtual void Draw() override final;
	virtual void Update(float deltaTime) override;

	virtual void MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta) override final;
	virtual void MouseBtnPressed(sf::Mouse::Button btn) override final;

protected:
	void SetMenuOptionBox(const sf::RectangleShape& menuOptionBox);
	void AddMenuOption(const sf::Text& optionName, MenuCommand* pOptionFunction);
	void EnterSubmenu(Menu* pSubmenu);
	void ReturnToPrevMenu();

private:
	friend class MenuAttorney;
	void Init();
	void End();

private:
	MenuManager* pMgr; // Menu class DOES NOT OWN this pointer
	sf::Text menuTitle;
	sf::Vector2f firstBoxPos;
	float boxVertSpacing;
	sf::Vector2f textOffsetInBox;
	sf::Color boxColorBase;
	sf::Color boxColorHighlight;
	std::vector<sf::Color> boxColors;
	sf::Color textColorBase;
	sf::Color textColorHighlight;
	MenuOptionList menuOptions; // Menu class DOES OWN the MenuCommand pointers in this list
	sf::RectangleShape menuOptionBox;
	bool setMenuOptionBox; // flag to prevent running the menu if the menuOptionBox is not set
	std::vector<sf::Vector2f> boxPositions;
	int selected;
	bool setMenuOptionsList; // flag to prevent running the menu if the menuOptions list is not set
};

#endif