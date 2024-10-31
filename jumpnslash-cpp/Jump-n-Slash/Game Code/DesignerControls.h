#ifndef DESIGNER_CONTROLS_H
#define DESIGNER_CONTROLS_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

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

// gamepad controls

//const int GP_JUMP; // not yet in use
//const sf::Joystick::Axis GP_WALK; // not yet in use
//const int GP_SLASH_ATK; // not yet in use
//const int GP_DREAM_ATK; // not yet in use
//const int GP_DASH; // not yet in use

///////////////////////
// player properties //
///////////////////////

const float PLAYER_WALK_SPEED = 100.0f;
const float GRAVITY_WEIGHT = 10.0f;
const float JUMP_FORCE = -400.0f;
const float MAX_JUMP_HOLD_TIME = 0.0f;

#endif
