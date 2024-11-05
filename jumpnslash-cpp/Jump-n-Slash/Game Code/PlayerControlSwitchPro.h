#ifndef PLAYER_CONTROL_SWITCH_PRO_H
#define PLAYER_CONTROL_SWITCH_PRO_H

#include "PlayerControlStrategy.h"

// forward declarations
class Player;

class PlayerControlSwitchPro : public PlayerControlStrategy
{
public:
	PlayerControlSwitchPro() = delete;
	PlayerControlSwitchPro(Player* pPlayer);
	PlayerControlSwitchPro(const PlayerControlSwitchPro& pcsp) = delete;
	PlayerControlSwitchPro& operator=(const PlayerControlSwitchPro& pcsp) = delete;
	virtual ~PlayerControlSwitchPro() = default;

	virtual void GamepadBtnPressed(int gamepadIndex, int btnNum) override;
	virtual void GamepadBtnReleased(int gamepadIndex, int btnNum) override;
	virtual void GamepadAxisMoved(int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta) override;
};

#endif