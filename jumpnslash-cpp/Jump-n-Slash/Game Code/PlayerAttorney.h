#ifndef PLAYER_ATTORNEY_H
#define PLAYER_ATTORNEY_H

#include <SFML/System/Vector2.hpp>

// forward declarations
class Player;
class LevelMap;

class PlayerAttorney
{
public:
	class State
	{
	private:
		friend class PlayerStateIdle;
		friend class PlayerStateWalking;
		friend class PlayerStateJumping;
		friend class PlayerStateFalling;

		// accessors

		static sf::Vector2f GetPos(Player* pPlayer);
		static sf::Vector2f GetPosDelta(Player* pPlayer);
		static LevelMap* GetLevel(Player* pPlayer);

		// mutators

		static void SetPosX(Player* pPlayer, float newX);
		static void SetPosY(Player* pPlayer, float newY);
	};
};

#endif