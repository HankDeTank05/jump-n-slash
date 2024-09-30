#ifndef LEVEL_0_H
#define LEVEL_0_H

#include "../Engine Code/Scene.h"

// forward declarations
class Player;
class LevelMap;

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
	Player* pPlayer;
	LevelMap* pMap; // TODO: THIS IS A BASTARDIZATION OF THE SYSTEM, DO NOT DO THIS!!! THIS IS ONLY HERE FOR TESTING!!!
};

#endif