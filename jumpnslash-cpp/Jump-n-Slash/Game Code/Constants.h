#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// general constants

const int TILE_SIZE = 32;
const float TILE_SIZE_F = static_cast<float>(TILE_SIZE);
const std::string ASSET_SETUP_FILE = "assets/assetSetupFile_test.txt";

// controller constants

const std::string spGamepadName = "Pro Controller";
const std::string dsGamepadName = "DualSense Wireless Controller";

// LevelMap constants

const int MAX_LEVEL_SIZE = 1024;
const int ROOM_TILE_WIDTH = 40;
const int ROOM_TILE_HEIGHT = 20;

// level tile keys, for ease of use

const std::string KEY_BLOCK_BREAKABLE = "block breakable";
const std::string KEY_BLOCK_HAZARD = "block hazard";
const std::string KEY_BLOCK_SOLID = "block solid";
const std::string KEY_PLATFORM_SEMISOLID = "platform semisolid";
const std::string KEY_INDICATOR_ROOM_ORIGIN_START = "indicator room origin start";
const std::string KEY_INDICATOR_ROOM_ORIGIN = "indicator room origin";
const std::string KEY_INDICATOR_ROOM_WIDTH = "indicator room width";
const std::string KEY_INDICATOR_ROOM_HEIGHT = "indicator room height";
const std::string KEY_INDICATOR_SPAWN_PLAYER_LEFT = "indicator spawn player left";
const std::string KEY_INDICATOR_SPAWN_PLAYER_RIGHT = "indicator spawn player right";
const std::string KEY_INDICATOR_SPAWN_ENEMY_LEFT = "indicator spawn enemy left";
const std::string KEY_INDICATOR_SPAWN_ENEMY_RIGHT = "indicator spawn enemy right";

#endif