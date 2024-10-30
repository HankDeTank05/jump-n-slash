#ifndef DESIGNER_CONTROLS_H
#define DESIGNER_CONTROLS_H

#include <SFML/Window/Keyboard.hpp>

// general settings

const float ANIMATION_FRAMERATE = 7.f;

// player controls
// TODO: add link to SFML docs

const sf::Keyboard::Key JUMP_KEY = sf::Keyboard::Space;
const sf::Keyboard::Key WALK_LEFT_KEY = sf::Keyboard::Left;
const sf::Keyboard::Key WALK_RIGHT_KEY = sf::Keyboard::Right;
const sf::Keyboard::Key SLASH_ATK_KEY = sf::Keyboard::V; // not yet in use
const sf::Keyboard::Key DREAM_ATK_KEY = sf::Keyboard::C; // not yet in use
const sf::Keyboard::Key DASH_KEY = sf::Keyboard::X; // not yet in use

// player properties

const float PLAYER_WALK_SPEED = 100.0f;
const float GRAVITY_WEIGHT = 10.0f;
const float JUMP_FORCE = -400.0f;
const float MAX_JUMP_HOLD_TIME = 0.0f;

#endif
