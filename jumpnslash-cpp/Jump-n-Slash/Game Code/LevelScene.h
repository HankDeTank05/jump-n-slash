#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "../Engine Code/Scene.h"

// forward declarations
class LevelMap;
class Player;

class LevelScene : public Scene
{
public:
	LevelScene() = delete;
	LevelScene(LevelMap* pMap, Player* pPlayer);
	LevelScene(const LevelScene& ls) = delete;
	LevelScene& operator=(const LevelScene& ls) = delete;
	virtual ~LevelScene() = default;

	virtual void Init() = 0;
	virtual void End() = 0;

protected:
	LevelMap* pMap;
	Player* pPlayer;
};

#endif