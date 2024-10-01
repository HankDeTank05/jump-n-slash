#ifndef PLAYER_ATTORNEY_H
#define PLAYER_ATTORNEY_H

#include <SFML/Graphics.hpp>

// forward declarations
class Player;

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
		static sf::Vector2f GetPos(Player* pPlayer);
		static sf::Vector2f GetPosDelta(Player* pPlayer);
	};
};

#endif