#ifndef PLAYER_CONTROL_DUAL_SENSE_H
#define PLAYER_CONTROL_DUAL_SENSE_H

#include "PlayerControlStrategy.h"

// forward declarations
class Player;

class PlayerControlDualSense : public PlayerControlStrategy
{
public:
	PlayerControlDualSense() = delete;
	PlayerControlDualSense(Player* pPlayer);
	PlayerControlDualSense(const PlayerControlDualSense& pcds) = delete;
	PlayerControlDualSense& operator=(const PlayerControlDualSense& pcds) = delete;
	virtual ~PlayerControlDualSense() = default;

	virtual void GamepadBtnPressed(int gamepadIndex, int btnNum) override;
	virtual void GamepadBtnReleased(int gamepadIndex, int btnNum) override;
	virtual void GamepadAxisMoved(int gamepadIndex, sf::Joystick::Axis axis, float axisState, float axisStateDelta) override;
};

#endif