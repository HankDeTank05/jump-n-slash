#include "PlayerAttorney.h"

#include "Player.h"

sf::Vector2f PlayerAttorney::StateAccess::GetPosDelta(Player* pPlayer)
{
	return pPlayer->GetPosDelta();
}

bool PlayerAttorney::StateAccess::IsGrounded(Player* pPlayer)
{
	return pPlayer->IsGrounded();
}

void PlayerAttorney::StateAccess::RaycastRight(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastRight(deltaTime);
}

void PlayerAttorney::StateAccess::RaycastLeft(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastLeft(deltaTime);
}

void PlayerAttorney::StateAccess::RaycastUp(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastUp(deltaTime);
}

void PlayerAttorney::StateAccess::RaycastDown(Player* pPlayer, float deltaTime)
{
	pPlayer->RaycastDown(deltaTime);
}

void PlayerAttorney::StateAccess::ApplyGravity(Player* pPlayer, float deltaTime)
{
	pPlayer->ApplyGravity(deltaTime);
}

void PlayerAttorney::StateAccess::ProcessInputs(Player* pPlayer, float deltaTime)
{
	pPlayer->ProcessInputs(deltaTime);
}

void PlayerAttorney::StateAccess::SetAnimationIdle(Player* pPlayer)
{
	pPlayer->SetAnimationIdle();
}

void PlayerAttorney::StateAccess::SetAnimationWalk(Player* pPlayer)
{
	pPlayer->SetAnimationWalk();
}

void PlayerAttorney::StateAccess::SetAnimationJump(Player* pPlayer)
{
	pPlayer->SetAnimationJump();
}

void PlayerAttorney::StateAccess::SetAnimationFall(Player* pPlayer)
{
	pPlayer->SetAnimationFall();
}

sf::Vector2f PlayerAttorney::LevelAccess::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}

void PlayerAttorney::LevelAccess::SetPos(Player* pPlayer, sf::Vector2f newPos)
{
	pPlayer->SetPos(newPos);
}

void PlayerAttorney::LevelAccess::SetCurrentRoom(Player* pPlayer, RoomData* pNextRoom)
{
	pPlayer->SetCurrentRoom(pNextRoom);
}

sf::Vector2f PlayerAttorney::Sword::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}
