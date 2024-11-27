#include "PlayerAttorney.h"

// game includes
#include "Player.h"

sf::Vector2f PlayerAttorney::StateAccess::GetPosDelta(Player* pPlayer)
{
	return pPlayer->GetPosDelta();
}

bool PlayerAttorney::StateAccess::IsGrounded(Player* pPlayer)
{
	return pPlayer->IsGrounded();
}

bool PlayerAttorney::StateAccess::IsHeadBonked(Player* pPlayer)
{
	return pPlayer->IsHeadBonked();
}

bool PlayerAttorney::StateAccess::IsApplyGravity(Player* pPlayer)
{
	return pPlayer->IsApplyGravity();
}

void PlayerAttorney::StateAccess::RaycastRight(Player* pPlayer)
{
	pPlayer->RaycastRight();
}

void PlayerAttorney::StateAccess::RaycastLeft(Player* pPlayer)
{
	pPlayer->RaycastLeft();
}

void PlayerAttorney::StateAccess::RaycastUp(Player* pPlayer)
{
	pPlayer->RaycastUp();
}

void PlayerAttorney::StateAccess::RaycastDown(Player* pPlayer)
{
	pPlayer->RaycastDown();
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

void PlayerAttorney::LevelAccess::SetPosition(Player* pPlayer, const sf::Vector2f& newPos)
{
	pPlayer->SetPosition(newPos);
}

void PlayerAttorney::LevelAccess::SetCurrentRoom(Player* pPlayer, RoomData* pNextRoom)
{
	pPlayer->SetCurrentRoom(pNextRoom);
}

sf::Vector2f PlayerAttorney::SwordAccess::GetPos(Player* pPlayer)
{
	return pPlayer->GetPos();
}

int PlayerAttorney::SwordAccess::GetFacing(Player* pPlayer)
{
	return pPlayer->GetFacing();
}

void PlayerAttorney::StrategyAccess::SetWalk(Player* pPlayer, float direction)
{
	pPlayer->SetWalk(direction);
}

void PlayerAttorney::StrategyAccess::SetJump(Player* pPlayer, bool enabled)
{
	pPlayer->SetJump(enabled);
}
