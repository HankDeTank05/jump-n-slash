#include "PlayerControlStrategy.h"

#include "ControlMapping.h"
#include "PlayerAttorney.h"

PlayerControlStrategy::PlayerControlStrategy(Player* _pPlayer, ControlScheme ctrl)
	: pPlayer(_pPlayer),
	jump(false),
	walk(0.f),
	slashAtk(false),
	dreamAtk(false),
	dash(false)
{
	switch (ctrl)
	{
	case ControlScheme::Keyboard:
		// jump
		RequestKeyRegistration(Keyboard::Game::JUMP, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::JUMP, KeyEvent::KeyRelease);
		// walk
		RequestKeyRegistration(Keyboard::Game::WALK_LEFT, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::WALK_LEFT, KeyEvent::KeyRelease);
		RequestKeyRegistration(Keyboard::Game::WALK_RIGHT, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::WALK_RIGHT, KeyEvent::KeyRelease);
		// attack
		RequestKeyRegistration(Keyboard::Game::SLASH_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::SLASH_ATK, KeyEvent::KeyRelease);
		RequestKeyRegistration(Keyboard::Game::DREAM_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::DREAM_ATK, KeyEvent::KeyRelease);
		// dash
		RequestKeyRegistration(Keyboard::Game::DASH, KeyEvent::KeyPress);
		RequestKeyRegistration(Keyboard::Game::DASH, KeyEvent::KeyRelease);
		// pause
		RequestKeyRegistration(Keyboard::Game::PAUSE, KeyEvent::KeyPress);
		break;
	case ControlScheme::SwitchPro:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SwitchPro::Game::WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SwitchPro::Game::WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::DASH), GamepadBtnEvent::BtnRelease);
		// pause
		RequestGamepadBtnRegistration(0, static_cast<int>(SwitchPro::Game::PAUSE), GamepadBtnEvent::BtnPress);
		break;
	case ControlScheme::DualSense:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DualSense::Game::WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DualSense::Game::WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::DASH), GamepadBtnEvent::BtnRelease);
		// pause
		RequestGamepadBtnRegistration(0, static_cast<int>(DualSense::Game::PAUSE), GamepadBtnEvent::BtnPress);
		break;
	default:
		assert(false); // crash if we don't recognize the specified control scheme
	}
}

void PlayerControlStrategy::GetInputs()
{
	PlayerAttorney::StrategyAccess::SetJump(pPlayer, jump);
	PlayerAttorney::StrategyAccess::SetWalk(pPlayer, walk);
}
