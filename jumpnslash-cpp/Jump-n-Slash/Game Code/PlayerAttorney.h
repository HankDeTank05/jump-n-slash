#ifndef PLAYER_ATTORNEY_H
#define PLAYER_ATTORNEY_H

#include <SFML/System/Vector2.hpp>

// forward declarations
class Player;
class LevelMap;
class RoomData;

class PlayerAttorney
{
public:
	class StateAccess
	{
	private:
		friend class PlayerStateIdle;
		friend class PlayerStateWalking;
		friend class PlayerStateJumping;
		friend class PlayerStateFalling;

		// accessors

		static sf::Vector2f GetPosDelta(Player* pPlayer);
		static bool IsGrounded(Player* pPlayer);
		static bool IsHeadBonked(Player* pPlayer);
		static bool IsApplyGravity(Player* pPlayer);

		// mutators

		static void RaycastRight(Player* pPlayer);
		static void RaycastLeft(Player* pPlayer);
		static void RaycastUp(Player* pPlayer);
		static void RaycastDown(Player* pPlayer);

		static void ApplyGravity(Player* pPlayer, float deltaTime);
		static void ProcessInputs(Player* pPlayer, float deltaTime);

		static void SetAnimationIdle(Player* pPlayer);
		static void SetAnimationWalk(Player* pPlayer);
		static void SetAnimationJump(Player* pPlayer);
		static void SetAnimationFall(Player* pPlayer);
	};
	class LevelAccess
	{
	private:
		friend class LevelMap;

		// accessors

		static sf::Vector2f GetPos(Player* pPlayer);

		// mutators

		static void SetPosition(Player* pPlayer, const sf::Vector2f& newPos);
		static void SetCurrentRoom(Player* pPlayer, RoomData* pNextRoom);
	};
	class SwordAccess
	{
	private:
		friend class Sword;
		static sf::Vector2f GetPos(Player* pPlayer);
		static float GetFacing(Player* pPlayer);
	};
	class StrategyAccess
	{
	private:
		friend class PlayerControlStrategy;

		// mutators

		static void SetWalk(Player* pPlayer, float direction);
		static void SetJump(Player* pPlayer, bool enabled);
	};
};

#endif