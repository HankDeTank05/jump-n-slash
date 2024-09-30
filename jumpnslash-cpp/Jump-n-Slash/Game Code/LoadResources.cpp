#include "../Engine Code/JumpSlashEngine.h"

#include <fstream>

//#include <nlohmann/json.hpp>

#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"

#include "Level0.h"

void JumpSlashEngine::LoadResources()
{
	TextureManager::LoadTexture("player idle 1", "player/idle_1_32.png");
	TextureManager::LoadTexture("player idle 2", "player/idle_2_32.png");
	TextureManager::LoadTexture("player idle 3", "player/idle_3_32.png");
	TextureManager::LoadTexture("player idle 4", "player/idle_4_32.png");

	SpriteManager::LoadSprite("player idle 1", "player idle 1");
	SpriteManager::LoadSprite("player idle 2", "player idle 2");
	SpriteManager::LoadSprite("player idle 3", "player idle 3");
	SpriteManager::LoadSprite("player idle 4", "player idle 4");

	// parse the json file for level tiles to add
	//std::ifstream file("..\\..\\..\\tools\\formatting_rules.json");
	//nlohmann::json data = nlohmann::json::parse(file);
	
	TextureManager::LoadTexture("block solid", "leveltiles/block_solid_32.png");

	SpriteManager::LoadSprite("block solid", "block solid");

	SetStartScene(new Level0());
}
