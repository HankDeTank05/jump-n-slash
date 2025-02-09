#ifndef TILESET_H
#define TILESET_H

// language includes
#include <map>
#include <string>
#include <list>

// forward declarations
class Sprite;

class Tileset
{
public:
	Tileset();
	Tileset(std::list<std::string> paletteList, std::list<Sprite*> sprList);
	Tileset(const Tileset& t) = delete;
	Tileset& operator=(const Tileset& t) = delete;
	virtual ~Tileset() = default;

	// accessors

	Sprite* GetTile(std::string paletteName);

	// mutators

	void AddTile(std::string paletteName, Sprite* pSprite);

private:
	std::map<std::string, Sprite*> skins; // key is palette name, value is pointer to corresponding sprite
};

#endif