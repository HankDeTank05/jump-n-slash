#ifndef GRID_MANAGER_H
#define GRID_MANAGER_H

#include <string>
#include <map>
#include <vector>

// forward declarations

class MapManager // this class is written as a singleton
{
private:
	static MapManager* pInstance;

	MapManager() = default;
	MapManager(const MapManager& gm) = delete;
	MapManager& operator=(const MapManager& gm) = delete;
	virtual ~MapManager();

	static MapManager& Instance();

public: // public api functions
	// TODO: docs for MapManager::LoadMap
	static void LoadMap(std::string key, std::string filename);
	// TODO: docs for MapManager::GetMap
	static std::vector<std::vector<std::string>>* GetMap(std::string key); 

private: // engine-only api functions
	friend class MapManagerAttorney;
	static void Terminate();

private: // private api backend functions
	void privLoadGrid(std::string key, std::string filename);
	std::vector<std::vector<std::string>>* privGetGrid(std::string key);

private: // member variables
	std::map<std::string, std::vector<std::vector<std::string>>*> grids; /*!< The map containing every grid loaded into the engine. >*/
	const std::string FOLDER_NAME = "assets/levels/"; /*!< The name of the folder that grid files will be loaded from. >*/
};

#endif