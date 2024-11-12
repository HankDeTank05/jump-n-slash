#include "PlayerControlStrategy.h"

#include "DesignerControls.h"
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
		RequestKeyRegistration(KB_GAME_JUMP, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_JUMP, KeyEvent::KeyRelease);
		// walk
		RequestKeyRegistration(KB_GAME_WALK_LEFT, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_WALK_LEFT, KeyEvent::KeyRelease);
		RequestKeyRegistration(KB_GAME_WALK_RIGHT, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_WALK_RIGHT, KeyEvent::KeyRelease);
		// attack
		RequestKeyRegistration(KB_GAME_SLASH_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_SLASH_ATK, KeyEvent::KeyRelease);
		RequestKeyRegistration(KB_GAME_DREAM_ATK, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_DREAM_ATK, KeyEvent::KeyRelease);
		// dash
		RequestKeyRegistration(KB_GAME_DASH, KeyEvent::KeyPress);
		RequestKeyRegistration(KB_GAME_DASH, KeyEvent::KeyRelease);
		// pause
		RequestKeyRegistration(KB_GAME_PAUSE, KeyEvent::KeyPress);
		break;
	case ControlScheme::SwitchPro:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SP_GAME_WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(SP_GAME_WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_DASH), GamepadBtnEvent::BtnRelease);
		// pause
		RequestGamepadBtnRegistration(0, static_cast<int>(SP_GAME_PAUSE), GamepadBtnEvent::BtnPress);
		break;
	case ControlScheme::DualSense:
		// jump
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_JUMP), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_JUMP), GamepadBtnEvent::BtnRelease);
		// walk
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DS_GAME_WALK), GamepadAxisEvent::AxisInputAny);
		RequestGamepadAxisRegistration(0, static_cast<sf::Joystick::Axis>(DS_GAME_WALK_ALT), GamepadAxisEvent::AxisInputAny);
		// attack
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_SLASH_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_SLASH_ATK), GamepadBtnEvent::BtnRelease);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_DREAM_ATK), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_DREAM_ATK), GamepadBtnEvent::BtnRelease);
		// dash
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_DASH), GamepadBtnEvent::BtnPress);
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_DASH), GamepadBtnEvent::BtnRelease);
		// pause
		RequestGamepadBtnRegistration(0, static_cast<int>(DS_GAME_PAUSE), GamepadBtnEvent::BtnPress);
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
