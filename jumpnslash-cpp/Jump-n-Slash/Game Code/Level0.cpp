#include "Level0.h"

#include "Player.h"

Level0::Level0()
	: pPlayer(nullptr)
{
	// do nothing
}

Level0::~Level0()
{
	if (pPlayer != nullptr)
	{
		delete pPlayer;
	}
}

void Level0::Init()
{
	pPlayer = new Player();
}

void Level0::End()
{
	delete pPlayer;
	pPlayer = nullptr;
}
