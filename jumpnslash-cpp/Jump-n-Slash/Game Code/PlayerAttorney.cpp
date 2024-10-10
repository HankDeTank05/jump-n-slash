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

bool PlayerAttorney::State::IsGrounded(Player* pPlayer)
{
	return pPlayer->IsGrounded();
}

void PlayerAttorney::State::RaycastRight(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastRight(deltaTime);
}

void PlayerAttorney::State::RaycastLeft(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastLeft(deltaTime);
}

void PlayerAttorney::State::RaycastUp(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastUp(deltaTime);
}

void PlayerAttorney::State::RaycastDown(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastDown(deltaTime);
}

void PlayerAttorney::State::ApplyGravity(Player* pPlayer, float deltaTime)
{
	pPlayer->ApplyGravity(deltaTime);
}
