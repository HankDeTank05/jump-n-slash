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

		// mutators

		static void RaycastRight(Player* pPlayer, float deltaTime);
		static void RaycastLeft(Player* pPlayer, float deltaTime);
		static void RaycastUp(Player* pPlayer, float deltaTime);
		static void RaycastDown(Player* pPlayer, float deltaTime);

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

		static void SetPos(Player* pPlayer, sf::Vector2f newPos);
		static void SetCurrentRoom(Player* pPlayer, RoomData* pNextRoom);
	};
	class SwordAccess
	{
	private:
		friend class Sword;
		static sf::Vector2f GetPos(Player* pPlayer);
	};
};

#endif