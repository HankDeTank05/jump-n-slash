#include "PlayerAttorney.h"

#include "Player.h"

sf::Vector2f PlayerAttorney::State::GetPosDelta(Player* pPlayer)
{
	return pPlayer->GetPosDelta();
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

void PlayerAttorney::State::ProcessInputs(Player* pPlayer, float deltaTime)
{
	pPlayer->ProcessInputs(deltaTime);
}

void PlayerAttorney::State::SetAnimationIdle(Player* pPlayer)
{
	pPlayer->SetAnimationIdle();
}

void PlayerAttorney::State::SetAnimationWalk(Player* pPlayer)
{
	pPlayer->SetAnimationWalk();
}

void PlayerAttorney::State::SetAnimationJump(Player* pPlayer)
{
	pPlayer->SetAnimationJump();
}

void PlayerAttorney::State::SetAnimationFall(Player* pPlayer)
{
	pPlayer->SetAnimationFall();
}

sf::Vector2f PlayerAttorney::Level::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}

void PlayerAttorney::Level::SetPos(Player* pPlayer, sf::Vector2f newPos)
{
	pPlayer->SetPos(newPos);
}

void PlayerAttorney::Level::SetCurrentRoom(Player* pPlayer, RoomData* pNextRoom)
{
	pPlayer->SetCurrentRoom(pNextRoom);
}
