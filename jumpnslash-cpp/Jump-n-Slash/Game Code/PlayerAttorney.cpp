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

LevelMap* PlayerAttorney::State::GetLevel(Player* pPlayer)
{
	return pPlayer->GetLevel();
}

void PlayerAttorney::State::SetPosX(Player* pPlayer, float newX)
{
	pPlayer->SetPosX(newX);
}

void PlayerAttorney::State::SetPosY(Player* pPlayer, float newY)
{
	pPlayer->SetPosY(newY);
}

void PlayerAttorney::State::RaycastRight(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastRight(deltaTime);
}

void PlayerAttorney::State::RaycastLeft(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastLeft(deltaTime);
}
