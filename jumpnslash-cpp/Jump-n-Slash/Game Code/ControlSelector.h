#ifndef CONTROL_SELECTOR_H
#define CONTROL_SELECTOR_H

#include <SFML/Graphics/Rect.hpp>

#include "../Engine Code/DrawObject.h"
#include "../Engine Code/UpdateObject.h"
#include "../Engine Code/InputObject.h"

#include "../Engine Code/ControlScheme.h"

class ControlSelector : public UpdateObject, public DrawObject, public InputObject
{
public:
	ControlSelector();
	ControlSelector(const ControlSelector& cs) = delete;
	ControlSelector& operator=(const ControlSelector& cs) = delete;
	virtual ~ControlSelector() = default;

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

	virtual void MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta) override;
	virtual void MouseBtnPressed(sf::Mouse::Button btn) override;

private:
	static const float BOX_W;
	static const float BOX_H;
	static const float BOX_W_SPACING;
	static const float BOX_X_START;
	ControlScheme ctrl;
	sf::RectangleShape kbSelectBox;
	sf::Text kbSelectText;
	sf::RectangleShape spSelectBox;
	sf::Text spSelectText;
	sf::RectangleShape dsSelectBox;
	sf::Text dsSelectText;
	sf::Vector2i mousePos;
	bool mouseClicked;
};

#endif