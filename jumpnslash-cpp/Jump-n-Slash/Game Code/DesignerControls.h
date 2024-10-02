#ifndef DESIGNER_CONTROLS_H
#define DESIGNER_CONTROLS_H

#include <SFML/Window/Keyboard.hpp>

// player controls
// TODO: add link to SFML docs

const sf::Keyboard::Key JUMP_KEY = sf::Keyboard::Up;
const sf::Keyboard::Key WALK_LEFT_KEY = sf::Keyboard::Left;
const sf::Keyboard::Key WALK_RIGHT_KEY = sf::Keyboard::Right;

// player properties

const float PLAYER_WALK_SPEED = 25.0f;
const float GRAVITY_WEIGHT = -1.0f;

#endif
