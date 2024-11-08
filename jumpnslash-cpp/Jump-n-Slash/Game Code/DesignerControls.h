#ifndef DESIGNER_CONTROLS_H
#define DESIGNER_CONTROLS_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

#include "../Engine Code/ControllerInputs.h"

//////////////////////
// general settings //
//////////////////////

const float ANIMATION_FRAMERATE = 7.f;

/////////////////////
// player controls //
/////////////////////

// for details on how input works, go here: https://www.sfml-dev.org/tutorials/2.6/window-inputs.php

// keyboard controls

const sf::Keyboard::Key KB_GAME_JUMP = sf::Keyboard::Space;
const sf::Keyboard::Key KB_GAME_WALK_LEFT = sf::Keyboard::Left;
const sf::Keyboard::Key KB_GAME_WALK_RIGHT = sf::Keyboard::Right;
const sf::Keyboard::Key KB_GAME_SLASH_ATK = sf::Keyboard::V; // not yet in use
const sf::Keyboard::Key KB_GAME_DREAM_ATK = sf::Keyboard::C; // not yet in use
const sf::Keyboard::Key KB_GAME_DASH = sf::Keyboard::X; // not yet in use
const sf::Keyboard::Key KB_GAME_PAUSE = sf::Keyboard::Escape; // not yet in use

const sf::Keyboard::Key KB_MENU_NAV_UP = sf::Keyboard::Up; // not yet in use
const sf::Keyboard::Key KB_MENU_NAV_DOWN = sf::Keyboard::Down; // not yet in use
const sf::Keyboard::Key KB_MENU_NAV_LEFT = sf::Keyboard::Left; // not yet in use
const sf::Keyboard::Key KB_MENU_NAV_RIGHT = sf::Keyboard::Right; // not yet in use
const sf::Keyboard::Key KB_MENU_SELECT = sf::Keyboard::Enter; // not yet in use
const sf::Keyboard::Key KB_MENU_BACK = sf::Keyboard::Backspace; // not yet in use

// gamepad controls (switch pro)

const SwitchProButton SP_GAME_JUMP = SwitchProButton::B;
const SwitchProAxis SP_GAME_WALK = SwitchProAxis::LeftStickHorizontal;
const SwitchProAxis SP_GAME_WALK_ALT = SwitchProAxis::DpadHorizontal;
const SwitchProButton SP_GAME_SLASH_ATK = SwitchProButton::Y; // not yet in use
const SwitchProButton SP_GAME_DREAM_ATK = SwitchProButton::X; // not yet in use
const SwitchProButton SP_GAME_DASH = SwitchProButton::ZL; // not yet in use
const SwitchProButton SP_GAME_PAUSE = SwitchProButton::Plus; // not yet in use

const SwitchProAxis SP_MENU_NAV_UP_DOWN = SwitchProAxis::LeftStickVertical; // not yet in use
const SwitchProAxis SP_MENU_NAV_LEFT_RIGHT = SwitchProAxis::LeftStickHorizontal; // not yet in use
const SwitchProAxis SP_MENU_NAV_UP_DOWN_ALT = SwitchProAxis::DpadVertical; // not yet in use
const SwitchProAxis SP_MENU_NAV_LEFT_RIGHT_ALT = SwitchProAxis::DpadHorizontal; // not yet in use
const SwitchProButton SP_MENU_SELECT = SwitchProButton::A; // not yet in use
const SwitchProButton SP_MENU_BACK = SwitchProButton::B; // not yet in use

// gamepad controls (dualsense)

const DualSenseButton DS_GAME_JUMP = DualSenseButton::X;
const DualSenseAxis DS_GAME_WALK = DualSenseAxis::LeftStickHorizontal;
const DualSenseAxis DS_GAME_WALK_ALT = DualSenseAxis::DpadHorizontal;
const DualSenseButton DS_GAME_SLASH_ATK = DualSenseButton::Square; // not yet in use
const DualSenseButton DS_GAME_DREAM_ATK = DualSenseButton::Triangle; // not yet in use
const DualSenseButton DS_GAME_DASH = DualSenseButton::L2Digital; // not yet in use
const DualSenseButton DS_GAME_PAUSE = DualSenseButton::Menu; // not yet in use

const DualSenseAxis DS_MENU_NAV_UP_DOWN = DualSenseAxis::LeftStickVertical; // not yet in use
const DualSenseAxis DS_MENU_NAV_LEFT_RIGHT = DualSenseAxis::LeftStickHorizontal; // not yet in use
const DualSenseAxis DS_MENU_NAV_UP_DOWN_ALT = DualSenseAxis::DpadVertical; // not yet in use
const DualSenseAxis DS_MENU_NAV_LEFT_RIGHT_ALT = DualSenseAxis::DpadHorizontal; // not yet in use
const DualSenseButton DS_MENU_SELECT = DualSenseButton::X; // not yet in use
const DualSenseButton DS_MENU_BACK = DualSenseButton::Circle; // not yet in use

///////////////////////
// player properties //
///////////////////////

const float PLAYER_WALK_SPEED = 100.0f;
const float GRAVITY_WEIGHT = 10.0f;
const float JUMP_FORCE = -400.0f;
const float MAX_JUMP_HOLD_TIME = 0.0f;

#endif
