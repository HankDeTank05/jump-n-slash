#include "PlayerControlStrategy.h"

#include "DesignerControls.h"
#include "PlayerAttorney.h"

PlayerControlStrategy::PlayerControlStrategy(Player* _pPlayer, ControlScheme scheme)
	: pPlayer(_pPlayer),
	jump(false),
	walk(0.f),
	slashAtk(false),
	dreamAtk(false),
	dash(false)
{
	switch (scheme)
	{
	case ControlScheme::Keyboard:
		// jump
		RequestKeyRegistration(KB_JUMP, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_JUMP, KeyEvent::KeyRelease);
		// walk
		RequestKeyRegistration(KB_WALK_LEFT, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_WALK_LEFT, KeyEvent::KeyRelease);
		RequestKeyRegistration(KB_WALK_RIGHT, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_WALK_RIGHT, KeyEvent::KeyRelease);
		// attack
		RequestKeyRegistration(KB_SLASH_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_SLASH_ATK, KeyEvent::KeyRelease);
		RequestKeyRegistration(KB_DREAM_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_DREAM_ATK, KeyEvent::KeyRelease);
		// dash
		RequestKeyRegistration(KB_DASH, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_DASH, KeyEvent::KeyRelease);
		break;
	case ControlScheme::SwitchPro:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SP_WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SP_WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_DASH), GamepadBtnEvent::BtnRelease);
		break;
	case ControlScheme::DualSense:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DS_WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DS_WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_DASH), GamepadBtnEvent::BtnRelease);
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
