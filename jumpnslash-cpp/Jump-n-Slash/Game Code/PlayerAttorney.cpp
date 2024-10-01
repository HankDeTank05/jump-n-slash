#include "PlayerAttorney.h"

#include "Player.h"

sf::Vector2f PlayerAttorney::State::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}

sf::Vector2f PlayerAttorney::State::GetPosDelta(Player* pPlayer)
{
	return pPlayer->GetPosDelta();
}
