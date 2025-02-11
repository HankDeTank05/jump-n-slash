#ifndef TILE_PROPERTIES_H
#define TILE_PROPERTIES_H

class TileProperties
{
public:
	TileProperties() = default;
	TileProperties(const TileProperties& tp) = delete;
	TileProperties& operator=(const TileProperties& tp) = delete;
	virtual ~TileProperties() = default;

private:
	bool solidOnTop;
	bool solidOnSides;
	bool solidOnBottom;

	float damageToPlayer;
	float damageToEnemies;
	float damageToBosses;
	float damageToNpcs;

	bool breakable;

	bool bouncy;

};

#endif