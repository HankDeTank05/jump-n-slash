#include "MapManager.h"

#include <fstream>

MapManager* MapManager::pInstance = nullptr;

MapManager::~MapManager()
{
	for (std::map<std::string, std::vector<std::vector<std::string>>*>::iterator it = grids.begin(); it != grids.end(); it++)
	{
		delete (*it).second;
	}

	grids.clear();
}

MapManager& MapManager::Instance()
{
	if (pInstance == nullptr)
	{
		pInstance = new MapManager();
	}
	return *pInstance;
}

void MapManager::LoadMap(std::string key, std::string filename)
{
	Instance().privLoadGrid(key, filename);
}

std::vector<std::vector<std::string>>* MapManager::GetMap(std::string key)
{
	return Instance().privGetGrid(key);
}

void MapManager::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

void MapManager::privLoadGrid(std::string key, std::string filename)
{
	assert(grids.count(key) == 0); // no duplicate keys!

	// parse the text file
	int y = 0;
	std::string line;
	std::ifstream file(FOLDER_NAME + filename);
	std::vector<std::vector<std::string>>* grid = new std::vector<std::vector<std::string>>();
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			grid->push_back(std::vector<std::string>());
			// split the line by spaces
			while (line.find(" ") != std::string::npos)
			{
				int size = line.size();
				int index = line.find(" ");
				grid->at(y).push_back(line.substr(0, 2));
				line = line.substr(index + 1, std::string::npos);
			}
			grid->at(y).push_back(line);
			y++;
		}
		file.close();
	}
	else
	{
		assert(false); // unable to open file
	}

	grids.emplace(key, grid);
}

std::vector<std::vector<std::string>>* MapManager::privGetGrid(std::string key)
{
	assert(grids.count(key) > 0); // if this assert got triggered, the key was not found in the map

	return grids.at(key);
}
