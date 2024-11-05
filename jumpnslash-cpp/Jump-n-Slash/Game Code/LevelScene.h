#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "../Engine Code/Scene.h"

#include "ControlScheme.h"

// forward declarations
class LevelMap;
class Player;

class LevelScene : public Scene
{
public:
	LevelScene() = delete;
	LevelScene(ControlScheme ctrl);
	LevelScene(const LevelScene& ls) = delete;
	LevelScene& operator=(const LevelScene& ls) = delete;
	virtual ~LevelScene() = default;

protected:
	LevelMap* pMap;
	Player* pPlayer;
};

#endif