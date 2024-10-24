#ifndef LEVEL_0_H
#define LEVEL_0_H

#include "../Engine Code/Scene.h"

// forward declarations
class LevelMap;
class Player;
class Enemy;

class Level0 : public Scene
{
public:
	Level0();
	Level0(const Level0& l0) = delete;
	Level0& operator=(const Level0& l0) = delete;
	virtual ~Level0();

	virtual void Init() override;
	virtual void End() override;

private:
	LevelMap* pMap;
	Player* pPlayer;
	Enemy* pEnemy;
};

#endif