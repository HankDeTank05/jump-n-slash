#ifndef ENGINE_CONSTANTS_H
#define ENGINE_CONSTANTS_H

// language includes
#include <string>

// library includes
#include <SFML/Graphics/Color.hpp>

// engine constants

const std::string WINDOW_NAME = "Jump n Slash";
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const unsigned int MAX_FRAMERATE = 60;

// GameObject constants

const int ALARM_COUNT = 10;

// visualizer default settings

const sf::Color VIZ_DEFAULT_COLOR = sf::Color::Cyan;
const float VIZ_DEFAULT_LINE_SIZE = 1.0f;
const float VIZ_POINT_RADIUS = 1.0f;
const int VIZ_DEFAULT_TEXT_SIZE = 15;

#endif