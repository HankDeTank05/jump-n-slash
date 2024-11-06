#include "ControlSelector.h"

#include "../Engine Code/Visualizer.h"
#include "../Engine Code/SceneManager.h"
#include "../Engine Code/FontManager.h"
#include "../Engine Code/ControlManager.h"

#include "Level0.h"

const float ControlSelector::BOX_W = 200.f;
const float ControlSelector::BOX_H = 50.f;
const float ControlSelector::BOX_W_SPACING = 10.f;
const float ControlSelector::BOX_X_START = 100.f;

ControlSelector::ControlSelector()
	: ctrl(ControlScheme::Keyboard),
	kbSelectBox(sf::Vector2f(BOX_W, BOX_H)),
	kbSelectText("Keyboard", *FontManager::GetFont("delfino")),
	spSelectBox(sf::Vector2f(BOX_W, BOX_H)),
	spSelectText("Switch Pro", *FontManager::GetFont("delfino")),
	dsSelectBox(sf::Vector2f(BOX_W, BOX_H)),
	dsSelectText("DualSense", *FontManager::GetFont("delfino")),
	mousePos(0, 0),
	mouseClicked(false)
{
	kbSelectBox.setPosition(BOX_X_START, 100.f);
	sf::Vector2f boxPos = kbSelectBox.getPosition();
	sf::Vector2f boxSize = kbSelectBox.getSize();
	kbSelectText.setFillColor(sf::Color::Black);
	kbSelectText.setPosition(
		((boxPos.x + (boxPos.x + boxSize.x)) / 2) - 75,
		((boxPos.y + (boxPos.y + boxSize.y)) / 2) - 20
	);
	// x pos = ((boxPos.x + (boxPos.x + boxSize.x)) / 2) - (textSize.x / 2)
	// y pos = ((boxPos.y + (boxPos.y + boxSize.y)) / 2) - (textSize.y / 2)

	spSelectBox.setPosition(BOX_X_START + (BOX_W + BOX_W_SPACING) * 1, 100.f);
	boxPos = spSelectBox.getPosition();
	boxSize = spSelectBox.getSize();
	spSelectText.setFillColor(sf::Color::Black);
	spSelectText.setPosition(
		((boxPos.x + (boxPos.x + boxSize.x)) / 2) - 75,
		((boxPos.y + (boxPos.y + boxSize.y)) / 2) - 20
	);

	dsSelectBox.setPosition(BOX_X_START + (BOX_W + BOX_W_SPACING) * 2, 100.f);
	boxPos = dsSelectBox.getPosition();
	boxSize = dsSelectBox.getSize();
	dsSelectText.setFillColor(sf::Color::Black);
	dsSelectText.setPosition(
		((boxPos.x + (boxPos.x + boxSize.x)) / 2) - 75,
		((boxPos.y + (boxPos.y + boxSize.y)) / 2) - 20
	);

	RequestUpdateRegistration();
	RequestDrawRegistration();
	RequestMouseCursorRegistration();
	RequestMouseBtnRegistration(sf::Mouse::Left, MouseEvent::BtnPress);
}

void ControlSelector::Update(float deltaTime)
{
	if (kbSelectBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		kbSelectBox.setFillColor(sf::Color::Green);
		ctrl = ControlScheme::Keyboard;
	}
	else
	{
		kbSelectBox.setFillColor(sf::Color::White);
	}

	if (spSelectBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		spSelectBox.setFillColor(sf::Color::Green);
		ctrl = ControlScheme::SwitchPro;
	}
	else
	{
		spSelectBox.setFillColor(sf::Color::White);
	}

	if (dsSelectBox.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		dsSelectBox.setFillColor(sf::Color::Green);
		ctrl = ControlScheme::DualSense;
	}
	else
	{
		dsSelectBox.setFillColor(sf::Color::White);
	}

	if (mouseClicked == true)
	{
		ControlManager::SetControlScheme(ctrl);
		SceneManager::SetNextSceneChange(new Level0());
	}
}

void ControlSelector::Draw()
{
	Render(kbSelectBox);
	Render(kbSelectText);

	Render(spSelectBox);
	Render(spSelectText);

	Render(dsSelectBox);
	Render(dsSelectText);
}

void ControlSelector::MouseCursorMoved(sf::Vector2i pos, sf::Vector2i delta)
{
	mousePos = pos;
}

void ControlSelector::MouseBtnPressed(sf::Mouse::Button btn)
{
	switch (btn)
	{
	case sf::Mouse::Left:
		assert(mouseClicked == false);
		mouseClicked = true;
		break;
	}
}
