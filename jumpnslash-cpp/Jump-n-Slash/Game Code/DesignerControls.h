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

const sf::Keyboard::Key KB_JUMP = sf::Keyboard::Space;
const sf::Keyboard::Key KB_WALK_LEFT = sf::Keyboard::Left;
const sf::Keyboard::Key KB_WALK_RIGHT = sf::Keyboard::Right;
const sf::Keyboard::Key KB_SLASH_ATK = sf::Keyboard::V; // not yet in use
const sf::Keyboard::Key KB_DREAM_ATK = sf::Keyboard::C; // not yet in use
const sf::Keyboard::Key KB_DASH = sf::Keyboard::X; // not yet in use

// gamepad controls (switch pro)

const SwitchProButton SP_JUMP = SwitchProButton::B; // not yet in use
const SwitchProAxis SP_WALK = SwitchProAxis::LeftStickHorizontal; // not yet in use
const SwitchProAxis SP_WALK_ALT = SwitchProAxis::DpadHorizontal; // not yet in use
const SwitchProButton SP_SLASH_ATK = SwitchProButton::Y; // not yet in use
const SwitchProButton SP_DREAM_ATK = SwitchProButton::X; // not yet in use
const SwitchProButton SP_DASH = SwitchProButton::ZL; // not yet in use

const DualSenseButton DS_JUMP = DualSenseButton::X; // not yet in use
const DualSenseAxis DS_WALK = DualSenseAxis::LeftStickHorizontal; // not yet in use
const DualSenseAxis DS_WALK_ALT = DualSenseAxis::DpadHorizontal; // not yet in use
const DualSenseButton DS_SLASH_ATK = DualSenseButton::Square; // not yet in use
const DualSenseButton DS_DREAM_ATK = DualSenseButton::Triangle; // not yet in use
const DualSenseButton DS_DASH = DualSenseButton::L2Digital; // not yet in use

///////////////////////
// player properties //
///////////////////////

const float PLAYER_WALK_SPEED = 100.0f;
const float GRAVITY_WEIGHT = 10.0f;
const float JUMP_FORCE = -400.0f;
const float MAX_JUMP_HOLD_TIME = 0.0f;

#endif
