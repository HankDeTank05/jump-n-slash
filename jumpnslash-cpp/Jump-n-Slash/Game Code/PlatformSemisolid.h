#ifndef PLATFORM_SEMISOLID_H
#define PLATFORM_SEMISOLID_H

#include "LevelTile.h"

class PlatformSemisolid : public LevelTile
{
public:
	PlatformSemisolid() = delete;
	PlatformSemisolid(sf::Vector2f pos);
	PlatformSemisolid(const PlatformSemisolid& ps) = delete;
	PlatformSemisolid& operator=(const PlatformSemisolid& ps) = delete;
	virtual ~PlatformSemisolid();
};

#endif