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
#include "../Engine Code/Sprite.h"

// game includes
#include "AssetLoader.h"
#include "GameManager.h"

// game includes (designer controls)
#include "ControlMapping.h"
#include "ParamsPlayer.h"
#include "ParamsDreamcatchers.h"

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

	// set connectors for player sprites

	SpriteManager::GetSprite("player idle 1")->AddConnector("weapon hold", sf::Vector2f(31.f, 15.f), 0.f);
	SpriteManager::GetSprite("player idle 2")->AddConnector("weapon hold", sf::Vector2f(31.f, 16.f), 0.f);
	SpriteManager::GetSprite("player idle 3")->AddConnector("weapon hold", sf::Vector2f(31.f, 18.f), 0.f);
	SpriteManager::GetSprite("player idle 4")->AddConnector("weapon hold", sf::Vector2f(31.f, 19.f), 0.f);

	SpriteManager::GetSprite("player walk 1")->AddConnector("weapon hold", sf::Vector2f(31.f, 16.f), 0.f);
	SpriteManager::GetSprite("player walk 2")->AddConnector("weapon hold", sf::Vector2f(31.f, 16.f), 0.f);
	SpriteManager::GetSprite("player walk 3")->AddConnector("weapon hold", sf::Vector2f(31.f, 16.f), 0.f);
	SpriteManager::GetSprite("player walk 4")->AddConnector("weapon hold", sf::Vector2f(31.f, 16.f), 0.f);

	SpriteManager::GetSprite("player jump 1")->AddConnector("weapon hold", sf::Vector2f(26.f, 5.f), 0.f);
	SpriteManager::GetSprite("player jump 2")->AddConnector("weapon hold", sf::Vector2f(26.f, 5.f), 0.f);
	SpriteManager::GetSprite("player jump 3")->AddConnector("weapon hold", sf::Vector2f(26.f, 5.f), 0.f);
	SpriteManager::GetSprite("player jump 4")->AddConnector("weapon hold", sf::Vector2f(26.f, 5.f), 0.f);
	
	SpriteManager::GetSprite("player fall 1")->AddConnector("weapon hold", sf::Vector2f(26.f, 26.f), 0.f);
	SpriteManager::GetSprite("player fall 2")->AddConnector("weapon hold", sf::Vector2f(26.f, 26.f), 0.f);
	SpriteManager::GetSprite("player fall 3")->AddConnector("weapon hold", sf::Vector2f(26.f, 26.f), 0.f);
	SpriteManager::GetSprite("player fall 4")->AddConnector("weapon hold", sf::Vector2f(26.f, 26.f), 0.f);

	SpriteManager::GetSprite("player attack 1")->AddConnector("weapon hold", sf::Vector2f(31.f, 15.f), 0.f);
	SpriteManager::GetSprite("player attack 2")->AddConnector("weapon hold", sf::Vector2f(31.f, 15.f), 0.f);
	SpriteManager::GetSprite("player attack 3")->AddConnector("weapon hold", sf::Vector2f(31.f, 15.f), 0.f);
	SpriteManager::GetSprite("player attack 4")->AddConnector("weapon hold", sf::Vector2f(31.f, 15.f), 0.f);

	SpriteManager::GetSprite("sword idle 1")->AddConnector("hold", sf::Vector2f(0.f, 23.f), 0.f);

	SpriteManager::GetSprite("sword swing 1")->AddConnector("hold", sf::Vector2f(0.f, 23.f), 0.f);
	SpriteManager::GetSprite("sword swing 2")->AddConnector("hold", sf::Vector2f(0.f, 23.f), 0.f);
	SpriteManager::GetSprite("sword swing 3")->AddConnector("hold", sf::Vector2f(0.f, 23.f), 0.f);
	SpriteManager::GetSprite("sword swing 4")->AddConnector("hold", sf::Vector2f(0.f, 23.f), 0.f);

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

	TextureManager::LoadTexture("paper mario spritesheet", "test/paper_mario.png");
	SpriteManager::LoadSprite("paper mario body", "paper mario spritesheet", sf::IntRect(1022, 2564, 148, 135));
	SpriteManager::LoadSprite("paper mario arm front", "paper mario spritesheet", sf::IntRect(105, 2569, 93, 105));
	SpriteManager::LoadSprite("paper mario arm back", "paper mario spritesheet", sf::IntRect(200, 2570, 87, 95));
	SpriteManager::LoadSprite("paper mario hand front", "paper mario spritesheet", sf::IntRect(37, 3789, 125, 114));
	SpriteManager::LoadSprite("paper mario hand back", "paper mario spritesheet", sf::IntRect(748, 3963, 119, 119));

	// asserts to make sure player parameters are set properly
	assert(Movement::GROUNDED_HORIZONTAL_MOVE_SPEED > 0.f);
	assert(Movement::PLAYER_GRAVITY > 0.f);
	assert(JUMP_FORCE < 0.f);
	assert(Movement::JUMP_RISING_SPEED > 0.f);

	// asserts to make sure dreamcatcher parameters are set properly

	assert(Ghost::Slash::HEX_DURATION >= 0.f); // hex duration must not be negative!
	assert(Ghost::Slash::HIT_FREQUENCY > 0.f); // hit frequency must be a positive number!
	assert(Ghost::Slash::HEX_DAMAGE > 0.f); // damage per hit must be a positive number!
	assert(Ghost::Slash::HEX_TRANSMISSIBILITY >= 0); // transmissibility must not be negative!
	assert(Ghost::Slash::MAX_HEX_COUNT >= 1); // hex coexistence count must be at least 1!
	assert(Ghost::Slash::MAX_HEXES_PER_ENEMY >= 1); // max hexes per enemy must be at least 1!

	assert(Ghost::Dream::MAX_AIMING_TIME > 0.f); // max aiming time must be a positive number!
	assert(Ghost::Dream::SPHERE_RADIUS > 0.f); // projectile radius must be a positive number!
	assert(Ghost::Dream::SPHERE_DAMAGE > 0.f); // projectile damage must be a positive number!
	assert(Ghost::Dream::SPHERE_LIFETIME > 0.f); // projectile lifetime must be a positive number!
	assert(Ghost::Dream::SPHERE_SPEED > 0.f); // projectile speed must be a positive number!
	assert(Ghost::Dream::MAX_COEXISTING_SPHERES >= 1); // max coexisting projectile count must be a positive number!
	assert(Ghost::Dream::ROTATION_SPEED > 0.f); // projectile rotation speed must be a positive number!
	assert(Ghost::Dream::HOMING_CONE_ANGLE > 0.f); // homing cone angle must be a positive number!
	assert(Ghost::Dream::HOMING_CONE_ANGLE <= 360.f); // homing cone angle must be no larger than 360 degrees!
	assert(Ghost::Dream::DREAM_ENERGY_USAGE > 0.f); // dream energy usage must be a positive number!
	
	assert(Ghost::Jump::INVINCIBILITY_TIME >= 0.f); // jump invincibility time must not be a negative number!

	assert(Ghost::Dash::INVINCIBILITY_TIME >= 0.f); // dash invincibility time must not be a negative number!
	assert(Ghost::Dash::DEGREE_OF_DI > 0.f); // degree of DI must be a positive number!
	assert(Ghost::Dash::DEGREE_OF_DI <= 1.f); // degree of DI must not be larger than 1.0!
	assert(Ghost::Dash::MAXIMUM_DI_DELTA > 0.f); // max DI delta must be a positive number!
	assert(Ghost::Dash::MAXIMUM_DI_DELTA <= 90.f); // max DI delta must not be larger than 90 degrees!

	// angel - slash attack
	
	// angel - dream attack

	// angel - jump

	// angel - dash

	// lightning - slash attack

	// lightning - dream attack

	// lightning - jump

	// lightning - dash

	// shield - slash attack

	// shield - dream attack

	// shield - jump

	// shield - dash

	// escape key cannot be used for any controls, as it is reserved for closing the window
	assert(Keyboard::Game::JUMP != sf::Keyboard::Escape); // TODO: make an engine constant for this instead of hard-coding it
	assert(Keyboard::Game::WALK_LEFT != sf::Keyboard::Escape);
	assert(Keyboard::Game::WALK_RIGHT != sf::Keyboard::Escape);
	assert(Keyboard::Game::SLASH_ATK != sf::Keyboard::Escape);
	assert(Keyboard::Game::DREAM_ATK != sf::Keyboard::Escape);
	assert(Keyboard::Game::DASH != sf::Keyboard::Escape);
	assert(Keyboard::Game::PAUSE != sf::Keyboard::Escape);
	assert(Keyboard::Menu::NAV_UP != sf::Keyboard::Escape);
	assert(Keyboard::Menu::NAV_DOWN != sf::Keyboard::Escape);
	assert(Keyboard::Menu::NAV_LEFT != sf::Keyboard::Escape);
	assert(Keyboard::Menu::NAV_RIGHT != sf::Keyboard::Escape);
	assert(Keyboard::Menu::SELECT != sf::Keyboard::Escape);
	assert(Keyboard::Menu::BACK != sf::Keyboard::Escape);

	GameManager::StartGame();
}
