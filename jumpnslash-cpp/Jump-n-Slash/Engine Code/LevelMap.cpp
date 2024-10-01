#include "LevelMap.h"

#include <string>
#include <fstream>

#include "JumpSlashEngine.h"
#include "SpriteManager.h"

//LevelMap::LevelMap()
//{
//	for (int y = 0; y < map.size(); y++)
//	{
//		for (int x = 0; x < map[y].size(); x++)
//		{
//			if (y == 0 || x == 0 || y == map.size() - 1 || x == map[y].size() - 1)
//			{
//				map[y][x] = SpriteManager::GetSprite("block solid");
//			}
//			else
//			{
//				map[y][x] = nullptr;
//			}
//		}
//	}
//
//	EnqueueForDrawRegistration();
//}

LevelMap::LevelMap(std::string filename)
	: map()
{
	// parse the text file
	int y = 0;
	std::string line;
	std::ifstream file(filename);
	std::vector<std::vector<std::string>> tempMap;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			tempMap.push_back(std::vector<std::string>());
			// split the line by spaces
			while (line.find(" ") != std::string::npos)
			{
				int size = line.size();
				int index = line.find(" ");
				tempMap[y].push_back(line.substr(0, 2));
				line = line.substr(index + 1, std::string::npos);
			}
			y++;
		}
		file.close();
	}
	else
	{
		assert(false); // unable to open file
	}

	for (int y = 0; y < tempMap.size(); y++)
	{
		for (int x = 0; x < tempMap[y].size(); x++)
		{
			std::string tileID = tempMap[y][x];
			if (tileID == "06" || tileID == "03" || tileID == "07" || tileID == "04" || tileID == "05")
			{
				map[y][x] = SpriteManager::GetSprite("block solid");
			}
		}
	}

}

LevelMap::~LevelMap()
{
	// do nothing
}

void LevelMap::Init()
{
	EnqueueForDrawRegistration();
}

void LevelMap::Draw()
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] != nullptr)
			{
				map[y][x]->setPosition(x * 32.0f, y * 32.0f);
				JumpSlashEngine::GetWindow().draw(*map[y][x]);
			}
		}
	}
}
