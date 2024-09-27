#include "PlayerAttorney.h"

#include "Player.h"

float PlayerAttorney::State::GetPosX(Player* pPlayer)
{
	return pPlayer->GetPosX();
}

float PlayerAttorney::State::GetPosY(Player* pPlayer)
{
	return pPlayer->GetPosY();
}

sf::Vector2f PlayerAttorney::State::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}

float PlayerAttorney::State::GetPosDeltaX(Player* pPlayer)
{
	return pPlayer->GetPosDeltaX();
}

float PlayerAttorney::State::GetPosDeltaY(Player* pPlayer)
{
	return pPlayer->GetPosDeltaY();
}

sf::Vector2f PlayerAttorney::State::GetPosDelta(Player* pPlayer)
{
	return pPlayer->GetPosDelta();
}
