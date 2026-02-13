#ifndef TILESET_MANAGER_H
#define TILESET_MANAGER_H

// language includes
#include <map>
#include <string>
#include <list>

// forward declarations
class Sprite;
class Tileset;

class TilesetManager // this class is written as a singleton
{
private:
	static TilesetManager* pInstance;

	TilesetManager() = default;
	TilesetManager(const TilesetManager& tm) = delete;
	TilesetManager& operator=(const TilesetManager& tm) = delete;
	virtual ~TilesetManager() = default;

	static TilesetManager& Instance();

public: // API functions
	static void LoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<std::string> sprKeyList);
	static void LoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<Sprite*> sprList);
	static Tileset* GetTileset(std::string tsKey);

private: // internal-only API functions (accessible thru attorney)
	static void Terminate();

private: // API backend functions
	void privLoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<std::string> sprKeyList);
	void privLoadTileset(std::string tsKey, std::list<std::string> paletteNames, std::list<Sprite*> sprList);
	Tileset* privGetTileset(std::string tsKey);

private: // member variables
	std::map<std::string, Tileset*> sets;
};

#endif