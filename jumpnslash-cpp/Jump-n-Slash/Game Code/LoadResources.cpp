#include "../Engine Code/JumpSlashEngine.h"

// language includes
//#include <fstream>
//#include <iostream>

// library includes
//#include <nlohmann/json.hpp>
//#include <simdjson.h>

// engine includes
#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/FontManager.h"
#include "../Engine Code/GridManager.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/Animation.h"
#include "../Engine Code/SceneManager.h"

// game includes
#include "DesignerControls.h"
#include "AssetLoader.h"
#include "GameManager.h"

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

	// ^^^ the AssetLoader automates a lot, but...
	// anything that isn't/can't be automated should happen below vvv

	AnimationManager::GetAnimation("player jump")->SetLoop(false);
	AnimationManager::GetAnimation("player fall")->SetLoop(false);

	// parse the json file for level tiles to add
	// vvv for nlohman/json vvv
	//std::ifstream file("..\\..\\..\\tools\\formatting_rules.json");
	//json data = json::parse(file);
	// vvv for simdjson vvv
	//ondemand::parser parser;
	//padded_string json = padded_string::load("..\\..\\..\\tools\\formatting_rules.json");
	//ondemand::document jsonData = parser.iterate(json);
	//std::cout << "Tile size: " << jsonData["genericInfo"]["tileSize"] << std::endl;

	TextureManager::LoadTexture("block solid", "leveltiles/block_solid.png");
	SpriteManager::LoadSprite("block solid", "block solid");

	TextureManager::LoadTexture("platform semisolid", "leveltiles/platform_semisolid.png");
	SpriteManager::LoadSprite("platform semisolid", "platform semisolid");

	TextureManager::LoadTexture("indicator room height", "leveltiles/indicator_roomHeight.png");
	SpriteManager::LoadSprite("indicator room height", "indicator room height");

	TextureManager::LoadTexture("indicator room origin", "leveltiles/indicator_roomOrigin.png");
	SpriteManager::LoadSprite("indicator room origin", "indicator room origin");

	TextureManager::LoadTexture("indicator room origin start", "leveltiles/indicator_roomOriginStart.png");
	SpriteManager::LoadSprite("indicator room origin start", "indicator room origin start");

	TextureManager::LoadTexture("indicator room width", "leveltiles/indicator_roomWidth.png");
	SpriteManager::LoadSprite("indicator room width", "indicator room width");

	TextureManager::LoadTexture("indicator spawn player right", "leveltiles/indicator_spawnPlayerRight.png");
	SpriteManager::LoadSprite("indicator spawn player right", "indicator spawn player right");

	//GridManager::LoadGrid("test", "test.txt");
	//GridManager::LoadGrid("test 2", "test2.txt");

	// asserts to make sure designer controls are set properly

	assert(PLAYER_WALK_SPEED > 0.f);
	assert(GRAVITY_WEIGHT > 0.f);
	assert(JUMP_FORCE < 0.f);
	assert(MAX_JUMP_HOLD_TIME >= 0.f);

	// escape key cannot be used for any controls, as it is reserved for closing the window
	assert(KB_GAME_JUMP != sf::Keyboard::Escape);
	assert(KB_GAME_WALK_LEFT != sf::Keyboard::Escape);
	assert(KB_GAME_WALK_RIGHT != sf::Keyboard::Escape);
	assert(KB_GAME_SLASH_ATK != sf::Keyboard::Escape);
	assert(KB_GAME_DREAM_ATK != sf::Keyboard::Escape);
	assert(KB_GAME_DASH != sf::Keyboard::Escape);
	assert(KB_GAME_PAUSE != sf::Keyboard::Escape);
	assert(KB_MENU_NAV_UP != sf::Keyboard::Escape);
	assert(KB_MENU_NAV_DOWN != sf::Keyboard::Escape);
	assert(KB_MENU_NAV_LEFT != sf::Keyboard::Escape);
	assert(KB_MENU_NAV_RIGHT != sf::Keyboard::Escape);
	assert(KB_MENU_SELECT != sf::Keyboard::Escape);
	assert(KB_MENU_BACK != sf::Keyboard::Escape);

	GameManager::StartGame();
}
