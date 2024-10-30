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

bool PlayerAttorney::State::IsHeadBonked(Player* pPlayer)
{
	return pPlayer->IsHeadBonked();
}

bool PlayerAttorney::State::IsApplyGravity(Player* pPlayer)
{
	return pPlayer->IsApplyGravity();
}

void PlayerAttorney::State::RaycastRight(Player* pPlayer)
{
	pPlayer->RaycastRight();
}

void PlayerAttorney::State::RaycastLeft(Player* pPlayer)
{
	pPlayer->RaycastLeft();
}

void PlayerAttorney::State::RaycastUp(Player* pPlayer)
{
	pPlayer->RaycastUp();
}

void PlayerAttorney::State::RaycastDown(Player* pPlayer)
{
	pPlayer->RaycastDown();
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
