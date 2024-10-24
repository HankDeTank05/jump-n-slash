#include "Level0.h"

#include "../Engine Code/GridManager.h"
#include "../Engine Code/SceneManager.h"
#include "../Engine Code/Camera.h"

#include "LevelMap.h"
#include "Player.h"
#include "Enemy.h"

Level0::Level0()
	: pMap(nullptr),
	pPlayer(nullptr),
	pEnemy(nullptr)
{
	// do nothing
}

Level0::~Level0()
{
	if (pEnemy != nullptr)
	{
		delete pEnemy;
	}
	if (pPlayer != nullptr)
	{
		delete pPlayer;
	}
	if (pMap != nullptr)
	{
		delete pMap;
	}
}

void Level0::Init()
{
	pMap = new LevelMap(GridManager::GetGrid("test2"));
	pPlayer = new Player();
	pEnemy = new Enemy();

	pPlayer->LinkToMap(pMap);
	pPlayer->AddObserver(pMap);

	SetCollisionPair<Player, Enemy>();

	float viewWidth = ROOM_TILE_WIDTH * TILE_SIZE_F;
	float viewHeight = ROOM_TILE_HEIGHT * TILE_SIZE_F;
	Camera* pCamera = SceneManager::GetCurrentScene()->GetCurrentCamera();
	pCamera->SetCenter(20.f * TILE_SIZE_F, 10.f * TILE_SIZE_F);
	pCamera->SetSize(viewWidth, viewHeight);
	pCamera->SetViewport(0.f, 0.f, viewWidth / static_cast<float>(WINDOW_WIDTH), viewHeight / static_cast<float>(WINDOW_HEIGHT));
}

void Level0::End()
{
	delete pEnemy;
	pEnemy = nullptr;

	delete pPlayer;
	pPlayer = nullptr;

	delete pMap;
	pMap = nullptr;
}
