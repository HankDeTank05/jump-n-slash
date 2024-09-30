#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <map>
#include <string>

// forward declarations
class LevelMap;

class MapManager // this class is written as a singleton
{
private:
	static MapManager* pInstance;

	MapManager() = default;
	MapManager(const MapManager& mm) = delete;
	MapManager& operator=(const MapManager& mm) = delete;
	virtual ~MapManager();

	static MapManager& Instance();

public: // api functions
	static void LoadMap(std::string key, std::string filename); // TODO: documentation for MapManager::LoadMap
	static LevelMap* GetMap(std::string key); // TODO: documentation for MapManager::GetMap

private: // private instance functions
	void privLoadMap(std::string key, std::string fileneame);
	LevelMap* privGetMap(std::string key);

private: // member variables
	std::map<std::string, LevelMap*> levelMaps;
	const std::string FOLDER_NAME = "assets/leveldata/";

private: // engine-only api functions
	friend class MapManagerAttorney;
	static void Terminate();
};

#endif