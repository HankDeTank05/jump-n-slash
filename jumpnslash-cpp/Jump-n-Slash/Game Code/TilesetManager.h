#ifndef TILESET_MANAGER_H
#define TILESET_MANAGER_H

// language includes
#include <map>
#include <string>

// forward declarations
class JsonNodeList;
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
	static void LoadTileset(std::string key, JsonNodeList* pJsonData);

private: // internal-only API functions (accessible thru attorney)
	static void Terminate();

private: // API backend functions
	void privLoadTileset(std::string key, JsonNodeList* pJsonData);

private: // member variables
	std::map<std::string, Tileset*> sets;
};

#endif