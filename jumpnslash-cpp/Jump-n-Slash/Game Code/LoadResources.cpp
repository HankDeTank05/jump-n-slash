#include "../Engine Code/JumpSlashEngine.h"

#include <fstream>

//#include <nlohmann/json.hpp>

#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/FontManager.h"
#include "../Engine Code/GridManager.h"

#include "Level0.h"

void JumpSlashEngine::LoadResources()
{
	FontManager::LoadFont("arial", "arial.ttf");
	FontManager::LoadFont("consolas", "consola.ttf");
	FontManager::LoadFont("delfino", "Delfino.ttf");

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

	TextureManager::LoadTexture("platform semisolid", "leveltiles/platform_semisolid_32.png");
	SpriteManager::LoadSprite("platform semisolid", "platform semisolid");

	TextureManager::LoadTexture("indicator room height", "leveltiles/indicator_room_height_32.png");
	SpriteManager::LoadSprite("indicator room height", "indicator room height");

	TextureManager::LoadTexture("indicator room origin", "leveltiles/indicator_room_origin_32.png");
	SpriteManager::LoadSprite("indicator room origin", "indicator room origin");

	TextureManager::LoadTexture("indicator room origin start", "leveltiles/indicator_room_origin_start_32.png");
	SpriteManager::LoadSprite("indicator room origin start", "indicator room origin start");

	TextureManager::LoadTexture("indicator room width", "leveltiles/indicator_room_width_32.png");
	SpriteManager::LoadSprite("indicator room width", "indicator room width");

	TextureManager::LoadTexture("indicator spawn player right", "leveltiles/indicator_spawn_player_right_32.png");
	SpriteManager::LoadSprite("indicator spawn player right", "indicator spawn player right");

	GridManager::LoadGrid("test", "test.txt");
	GridManager::LoadGrid("test 2", "test2.txt");

	SetStartScene(new Level0());
}
