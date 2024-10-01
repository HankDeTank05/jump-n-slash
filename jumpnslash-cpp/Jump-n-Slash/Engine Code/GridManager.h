#ifndef GRID_MANAGER_H
#define GRID_MANAGER_H

#include <string>
#include <map>
#include <vector>

// forward declarations

class GridManager // this class is written as a singleton
{
private:
	static GridManager* pInstance;

	GridManager() = default;
	GridManager(const GridManager& gm) = delete;
	GridManager& operator=(const GridManager& gm) = delete;
	virtual ~GridManager();

	static GridManager& Instance();

public: // public api functions
	static void LoadGrid(std::string key, std::string filename);
	static std::vector<std::vector<std::string>>* GetGrid(std::string key);

private: // engine-only api functions
	friend class GridManagerAttorney;
	static void Terminate();

private: // private api backend functions
	void privLoadGrid(std::string key, std::string filename);
	std::vector<std::vector<std::string>>* privGetGrid(std::string key);

private: // member variables
	std::map<std::string, std::vector<std::vector<std::string>>*> grids; /*!< The map containing every grid loaded into the engine. >*/
	const std::string FOLDER_NAME = "assets/leveldata/"; /*!< The name of the folder that grid files will be loaded from. >*/
};

#endif