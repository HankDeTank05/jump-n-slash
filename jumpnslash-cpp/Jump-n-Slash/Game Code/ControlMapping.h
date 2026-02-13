#ifndef CONTROL_MAPPING_H
#define CONTROL_MAPPING_H

// library includes
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>

// engine includes
#include "../Engine Code/ControllerInputs.h"

// for details on how input works, go here: https://www.sfml-dev.org/tutorials/2.6/window-inputs.php

// keyboard controls
namespace Keyboard
{
	// player character controls
	namespace Game
	{
		const sf::Keyboard::Key JUMP = sf::Keyboard::Space;
		const sf::Keyboard::Key WALK_LEFT = sf::Keyboard::Left;
		const sf::Keyboard::Key WALK_RIGHT = sf::Keyboard::Right;
		const sf::Keyboard::Key SLASH_ATK = sf::Keyboard::V;
		const sf::Keyboard::Key DREAM_ATK = sf::Keyboard::C; // not yet in use
		const sf::Keyboard::Key DASH = sf::Keyboard::X; // not yet in use
		const sf::Keyboard::Key PAUSE = sf::Keyboard::Backspace; // not yet in use
	}

	// menu controls
	namespace Menu
	{
		const sf::Keyboard::Key NAV_UP = sf::Keyboard::Up; // not yet in use
		const sf::Keyboard::Key NAV_DOWN = sf::Keyboard::Down; // not yet in use
		const sf::Keyboard::Key NAV_LEFT = sf::Keyboard::Left; // not yet in use
		const sf::Keyboard::Key NAV_RIGHT = sf::Keyboard::Right; // not yet in use
		const sf::Keyboard::Key SELECT = sf::Keyboard::Enter; // not yet in use
		const sf::Keyboard::Key BACK = sf::Keyboard::Backspace; // not yet in use
	}
}

// gamepad controls (switch pro)
namespace SwitchPro
{
	// player character controls
	namespace Game
	{
		const SwitchProButton JUMP = SwitchProButton::B;
		const SwitchProAxis WALK = SwitchProAxis::LeftStickHorizontal;
		const SwitchProAxis WALK_ALT = SwitchProAxis::DpadHorizontal;
		const SwitchProButton SLASH_ATK = SwitchProButton::Y; // not yet in use
		const SwitchProButton DREAM_ATK = SwitchProButton::X; // not yet in use
		const SwitchProButton DASH = SwitchProButton::ZL; // not yet in use
		const SwitchProButton PAUSE = SwitchProButton::Plus; // not yet in use
	}

	// menu controls
	namespace Menu
	{
		const SwitchProAxis NAV_UP_DOWN = SwitchProAxis::LeftStickVertical; // not yet in use
		const SwitchProAxis NAV_LEFT_RIGHT = SwitchProAxis::LeftStickHorizontal; // not yet in use
		const SwitchProAxis NAV_UP_DOWN_ALT = SwitchProAxis::DpadVertical; // not yet in use
		const SwitchProAxis NAV_LEFT_RIGHT_ALT = SwitchProAxis::DpadHorizontal; // not yet in use
		const SwitchProButton SELECT = SwitchProButton::A; // not yet in use
		const SwitchProButton BACK = SwitchProButton::B; // not yet in use
	}
}

// gamepad controls (dualsense)
namespace DualSense
{
	// player character controls
	namespace Game
	{
		const DualSenseButton JUMP = DualSenseButton::X;
		const DualSenseAxis WALK = DualSenseAxis::LeftStickHorizontal;
		const DualSenseAxis WALK_ALT = DualSenseAxis::DpadHorizontal;
		const DualSenseButton SLASH_ATK = DualSenseButton::Square; // not yet in use
		const DualSenseButton DREAM_ATK = DualSenseButton::Triangle; // not yet in use
		const DualSenseButton DASH = DualSenseButton::L2Digital; // not yet in use
		const DualSenseButton PAUSE = DualSenseButton::Menu; // not yet in use
	}

	// menu controls
	namespace Menu
	{
		const DualSenseAxis NAV_UP_DOWN = DualSenseAxis::LeftStickVertical; // not yet in use
		const DualSenseAxis NAV_LEFT_RIGHT = DualSenseAxis::LeftStickHorizontal; // not yet in use
		const DualSenseAxis NAV_UP_DOWN_ALT = DualSenseAxis::DpadVertical; // not yet in use
		const DualSenseAxis NAV_LEFT_RIGHT_ALT = DualSenseAxis::DpadHorizontal; // not yet in use
		const DualSenseButton SELECT = DualSenseButton::X; // not yet in use
		const DualSenseButton BACK = DualSenseButton::Circle; // not yet in use
	}
}

// gamepad controls (dualshock 4)
namespace DualShock4 // TODO: create a control mapping for DualShock 4 controllers
{
	// player character controls
	namespace Game
	{
		// mapping goes here
	}

	// menu controls
	namespace Menu
	{
		// mapping goes here
	}
}

// gamepad controls (xbox series)
namespace XboxSeries // TODO: create a control mapping for Xbox Series controllers
{
	// player character controls
	namespace Game
	{
		// mapping goes here
	}

	// menu controls
	namespace Menu
	{
		// mapping goes here
	}
}

// gamepad controls (Xbox One)
namespace XboxOne // TODO: create a control mapping for Xbox One controllers
{
	// player character controls
	namespace Game
	{
		// mapping goes here
	}

	// menu controls
	namespace Menu
	{
		// mapping goes here
	}
}

// gamepad controls (Xbox 360)
namespace Xbox360 // TODO: create a control mapping for Xbox 360 controllers
{
	// player character controls
	namespace Game
	{
		// mapping goes here
	}

	// menu controls
	namespace Menu
	{
		// mapping goes here
	}
}

#endif
