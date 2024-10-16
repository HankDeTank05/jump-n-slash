#include "../Engine Code/JumpSlashEngine.h"

//#include <fstream>
//#include <iostream>

//#include <nlohmann/json.hpp>
//#include <simdjson.h>

#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/FontManager.h"
#include "../Engine Code/GridManager.h"
#include "../Engine Code/SceneManager.h"

#include "Level0.h"
#include "DesignerControls.h"
#include "AssetLoader.h"

//using namespace simdjson;
//using json = nlohmann::json;

void JumpSlashEngine::LoadResources()
{
	// load fonts
	FontManager::LoadFont("arial", "arial.ttf");
	FontManager::LoadFont("consolas", "consola.ttf");
	FontManager::LoadFont("delfino", "Delfino.ttf");

	AssetLoader loader;
	loader.ReadAssetSetupFile();

	// load player idle animation
	//TextureManager::LoadTexture("player idle 1", "player/idle_1_32.png");
	//TextureManager::LoadTexture("player idle 2", "player/idle_2_32.png");
	//TextureManager::LoadTexture("player idle 3", "player/idle_3_32.png");
	//TextureManager::LoadTexture("player idle 4", "player/idle_4_32.png");
	//SpriteManager::LoadSprite("player idle 1", "player idle 1");
	//SpriteManager::LoadSprite("player idle 2", "player idle 2");
	//SpriteManager::LoadSprite("player idle 3", "player idle 3");
	//SpriteManager::LoadSprite("player idle 4", "player idle 4");

	// load player walk animation
	TextureManager::LoadTexture("player walk 1", "player/walk_1_32.png");
	TextureManager::LoadTexture("player walk 2", "player/walk_2_32.png");
	TextureManager::LoadTexture("player walk 3", "player/walk_3_32.png");
	TextureManager::LoadTexture("player walk 4", "player/walk_4_32.png");
	SpriteManager::LoadSprite("player walk 1", "player walk 1");
	SpriteManager::LoadSprite("player walk 2", "player walk 2");
	SpriteManager::LoadSprite("player walk 3", "player walk 3");
	SpriteManager::LoadSprite("player walk 4", "player walk 4");

	// load player jump animation
	TextureManager::LoadTexture("player jump 1", "player/jump_1_32.png");
	TextureManager::LoadTexture("player jump 2", "player/jump_2_32.png");
	TextureManager::LoadTexture("player jump 3", "player/jump_3_32.png");
	TextureManager::LoadTexture("player jump 4", "player/jump_4_32.png");
	SpriteManager::LoadSprite("player jump 1", "player jump 1");
	SpriteManager::LoadSprite("player jump 2", "player jump 2");
	SpriteManager::LoadSprite("player jump 3", "player jump 3");
	SpriteManager::LoadSprite("player jump 4", "player jump 4");

	// load player fall animation
	TextureManager::LoadTexture("player fall 1", "player/fall_1_32.png");
	TextureManager::LoadTexture("player fall 2", "player/fall_2_32.png");
	TextureManager::LoadTexture("player fall 3", "player/fall_3_32.png");
	TextureManager::LoadTexture("player fall 4", "player/fall_4_32.png");
	SpriteManager::LoadSprite("player fall 1", "player fall 1");
	SpriteManager::LoadSprite("player fall 2", "player fall 2");
	SpriteManager::LoadSprite("player fall 3", "player fall 3");
	SpriteManager::LoadSprite("player fall 4", "player fall 4");

	// parse the json file for level tiles to add

	//std::ifstream file("..\\..\\..\\tools\\formatting_rules.json");
	//json data = json::parse(file);

	//ondemand::parser parser;
	//padded_string json = padded_string::load("..\\..\\..\\tools\\formatting_rules.json");
	//ondemand::document jsonData = parser.iterate(json);
	//std::cout << "Tile size: " << jsonData["genericInfo"]["tileSize"] << std::endl;

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

	// asserts to make sure designer controls are set properly
	assert(PLAYER_WALK_SPEED > 0.f);
	assert(GRAVITY_WEIGHT > 0.f);
	assert(JUMP_FORCE < 0.f);
	assert(MAX_JUMP_HOLD_TIME >= 0.f);

	SceneManager::SetStartScene(new Level0());
}
