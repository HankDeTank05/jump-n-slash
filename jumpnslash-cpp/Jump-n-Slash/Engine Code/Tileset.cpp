#include "Tileset.h"

Tileset::Tileset()
	: skins()
{
	// do nothing
}

Tileset::Tileset(std::list<std::string> paletteList, std::list<Sprite*> sprList)
	: skins()
{
	assert(paletteList.size() == sprList.size());

	std::list<std::string>::iterator paletteIt = paletteList.begin();
	std::list<Sprite*>::iterator sprIt = sprList.begin();

	while (paletteIt != paletteList.end() && sprIt != sprList.end())
	{
		skins.emplace(*paletteIt, *sprIt);

		paletteIt++;
		sprIt++;
	}
}

Sprite* Tileset::GetTile(std::string paletteName)
{
	assert(skins.count(paletteName) > 0);

	return skins.at(paletteName);
}

void Tileset::AddTile(std::string paletteName, Sprite* pSprite)
{
	assert(skins.count(paletteName) == 0);
	assert(pSprite != nullptr);

	skins.emplace(paletteName, pSprite);
}
