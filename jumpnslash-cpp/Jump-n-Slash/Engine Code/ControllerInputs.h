#ifndef CONTROLLER_INPUTS_H
#define CONTROLLER_INPUTS_H

// library includes
#include <SFML/Window/Joystick.hpp>

enum class SwitchProButton
{
	B = 0,
	A = 1,
	Y = 2,
	X = 3,
	L = 4,
	R = 5,
	ZL = 6,
	ZR = 7,
	Minus = 8,
	Plus = 9,
	LeftStickClick = 10,
	RightStickClick = 11,
	Home = 12,
	Capture = 13,
};

enum class SwitchProAxis
{
	LeftStickHorizontal = sf::Joystick::Axis::X,
	LeftStickVertical = sf::Joystick::Axis::Y,
	RightStickHorizontal = sf::Joystick::Axis::U,
	RightStickVertical = sf::Joystick::Axis::V,
	DpadHorizontal = sf::Joystick::Axis::PovX,
	DpadVertical = sf::Joystick::Axis::PovY
};

enum class DualSenseButton
{
	Square = 0,
	X = 1,
	Circle = 2,
	Triangle = 3,
	L1 = 4,
	R1 = 5,
	L2Digital = 6,
	R2Digital = 7,
	Share = 8,
	Menu = 9,
	L3 = 10,
	R3 = 11,
	PlayStation = 12,
	Touchpad = 13,
	MicMuteToggle = 14
};

enum class DualSenseAxis
{
	LeftStickHorizontal = sf::Joystick::Axis::X,
	LeftStickVertical = sf::Joystick::Axis::Y,
	RightStickHorizontal = sf::Joystick::Axis::Z,
	RightStickVertical = sf::Joystick::Axis::R,
	L2Analog = sf::Joystick::Axis::U,
	R2Analog = sf::Joystick::Axis::V,
	DpadHorizontal = sf::Joystick::PovX,
	DpadVertical = sf::Joystick::Axis::PovY
};

enum class DualShock4Button
{
	// TODO: determine DualShock 4 controller buttons
};

enum class DualShock4Axis
{
	// TODO: determine DualShock 4 controller axes
};

enum class XboxSeriesButton
{
	// TODO: determine Xbox Series controller buttons
};

enum class XboxSeriesAxis
{
	// TOOD: determine Xbox Series controller axes
};

enum class XboxOneButton
{
	// TODO: determine Xbox One controller buttons
};

enum class XboxOneAxes
{
	// TODO: determine Xbox One controller axes
};

enum class Xbox360Button
{
	// TODO: determine Xbox 360 controller buttons
};

enum class Xbox360Axes
{
	// TODO: determine Xbox 360 controller axes
};

#endif