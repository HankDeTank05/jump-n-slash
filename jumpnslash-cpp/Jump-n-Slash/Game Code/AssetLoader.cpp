#include "AssetLoader.h"

// language includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

// engine includes
#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/AnimationManager.h"
#include "../Engine Code/MapManager.h"

// game includes
#include "Constants.h"
#include "ParamsPlayer.h"
#include "GameDebugFlags.h"
#include "TextParser.h"

const std::string AssetLoader::COMMAND_TEXTURE = "texture";
const std::string AssetLoader::COMMAND_SPRITE = "sprite";
const std::string AssetLoader::COMMAND_ANIMATION = "animation";
const std::string AssetLoader::COMMAND_GRID = "grid";


AssetLoader::AssetLoader()
	: commands(),
	texturesToLoad()
{
	// define the "texture" command

	std::list<std::string> textureArgs;
	textureArgs.push_back(TextParser::TYPE_STRING); // texture key
	textureArgs.push_back(TextParser::TYPE_STRING); // file name
	textureArgs.push_back(TextParser::TYPE_BOOL); // smooth
	commands.emplace(AssetLoader::COMMAND_TEXTURE, textureArgs);

	// define the "sprite" command

	std::list<std::string> spriteArgs;
	spriteArgs.push_back(TextParser::TYPE_STRING); // sprite key
	spriteArgs.push_back(TextParser::TYPE_STRING); // texture key
	spriteArgs.push_back(TextParser::TYPE_INT); // texture x origin
	spriteArgs.push_back(TextParser::TYPE_INT); // texture y origin
	spriteArgs.push_back(TextParser::TYPE_INT); // texture width
	spriteArgs.push_back(TextParser::TYPE_INT); // texture height
	commands.emplace(AssetLoader::COMMAND_SPRITE, spriteArgs);

	// define the "animation" command

	std::list<std::string> animArgs;
	animArgs.push_back(TextParser::TYPE_STRING); // animation key
	animArgs.push_back(TextParser::TYPE_LIST_STRING); // list of sprite keys
	// NOTE: there is no argument for animation fps here, since we set that in DesignerControls.h
	animArgs.push_back(TextParser::TYPE_BOOL); // loop flag
	commands.emplace(AssetLoader::COMMAND_ANIMATION, animArgs);

	// define the "grid" command

	std::list<std::string> gridArgs;
	gridArgs.push_back(TextParser::TYPE_STRING); // grid key
	gridArgs.push_back(TextParser::TYPE_STRING); // filename
	commands.emplace(AssetLoader::COMMAND_GRID, gridArgs);
}

AssetLoader::~AssetLoader()
{
	// do nothing (yet)
}

void AssetLoader::ReadAssetSetupFile()
{
	// parse a text file

	std::string line;

	std::ifstream assetSetupFile = std::ifstream(ASSET_SETUP_FILE);

	// parse a line of text
	while (std::getline(assetSetupFile, line))
	{
		int strIndex = 0;

		std::string command = "none";
		std::string currentChar = line.substr(0, 1);
		assert(currentChar != " "); // lines may not start with spaces!
		assert(currentChar != "\t"); // lines may not start with tab characters!

		// parse everything up to the first space character (command name)
		while (currentChar != " ")
		{
			strIndex++;
			currentChar = line.substr(strIndex, 1);
		}

		command = line.substr(0, strIndex);	

		assert(commands.count(command) > 0); // invalid command!
		ParseCommand(line, command);
	}
}

void AssetLoader::ParseCommand(std::string line, std::string command)
{
	//*
	if (command == AssetLoader::COMMAND_TEXTURE)
	{
		ParseTextureCommand(line);
	}
	else if (command == AssetLoader::COMMAND_SPRITE)
	{
		ParseSpriteCommand(line);
	}
	else if (command == AssetLoader::COMMAND_ANIMATION)
	{
		ParseAnimationCommand(line);
	}
	else if (command == AssetLoader::COMMAND_GRID)
	{
		ParseGridCommand(line);
	}
	else
	{
		assert(false);
	}
	//*/
	/*
	int startIndex = command.size() + 1;

	std::list<std::string> argTypes = commands.at(command);
	int argNum = 0;

	for (std::list<std::string>::iterator it = argTypes.begin(); it != argTypes.end(); it++)
	{
		std::string argType = (*it);
		if (argType == AssetLoader::TYPE_STRING)
		{
			std::pair<std::string, int> result = ParseForString(line, startIndex);
			startIndex = result.second;
			argNum++;
		}
		else if (argType == AssetLoader::TYPE_FLOAT)
		{
			assert(false);
		}
		else if (argType == AssetLoader::TYPE_INT)
		{
			assert(false);
		}
		else if (argType == AssetLoader::TYPE_BOOL)
		{
			std::pair<bool, int> result = ParseForBool(line, startIndex);
			startIndex = result.second;
			argNum++;
		}
		else
		{
			assert(false); // unrecognized data type definition
		}
	}
	//*/

	if (DEBUG_ASSET_LOAD_AUTOMATION) std::cout << "Successfully parsed the following asset command: " << line << std::endl;
}

void AssetLoader::ParseTextureCommand(std::string line)
{
	int startIndex = AssetLoader::COMMAND_TEXTURE.size() + 1;

	std::pair<std::string, int> result1;
	std::pair<std::string, int> result2;
	std::pair<bool, int> result3;

	result1 = TextParser::ParseForString(line, startIndex);
	startIndex = result1.second;

	result2 = TextParser::ParseForString(line, startIndex);
	startIndex = result2.second + 1; // +1 so we skip the expected space

	result3 = TextParser::ParseForBool(line, startIndex);

	std::string arg1 = result1.first;
	std::string arg2 = result2.first;
	bool arg3 = result3.first;

	TextureManager::LoadTexture(arg1, arg2, arg3);
}

void AssetLoader::ParseSpriteCommand(std::string line)
{
	int startIndex = AssetLoader::COMMAND_SPRITE.size() + 1;

	std::pair<std::string, int> result1;
	std::pair<std::string, int> result2;
	std::pair<int, int> result3;
	std::pair<int, int> result4;
	std::pair<int, int> result5;
	std::pair<int, int> result6;

	result1 = TextParser::ParseForString(line, startIndex);
	startIndex = result1.second;

	result2 = TextParser::ParseForString(line, startIndex);
	startIndex = result2.second;

	result3 = TextParser::ParseForInt(line, startIndex);
	startIndex = result3.second;

	result4 = TextParser::ParseForInt(line, startIndex);
	startIndex = result4.second;

	result5 = TextParser::ParseForInt(line, startIndex);
	startIndex = result5.second;

	result6 = TextParser::ParseForInt(line, startIndex);
	startIndex = result6.second;

	std::string arg1 = result1.first;
	std::string arg2 = result2.first;
	int arg3 = result3.first;
	int arg4 = result4.first;
	int arg5 = result5.first;
	int arg6 = result6.first;

	SpriteManager::LoadSprite(arg1, arg2, sf::IntRect(arg3, arg4, arg5, arg6));
}

void AssetLoader::ParseAnimationCommand(std::string line)
{
	int startIndex = AssetLoader::COMMAND_ANIMATION.size() + 1;

	std::pair<std::string, int> result1;
	std::pair<std::list<std::string>, int> result2;
	std::pair<bool, int> result3;

	result1 = TextParser::ParseForString(line, startIndex);
	startIndex = result1.second + 1; // +1 to skip the expected space

	result2 = TextParser::ParseForListString(line, startIndex);
	startIndex = result2.second + 1; // +1 to skip the expected space

	result3 = TextParser::ParseForBool(line, startIndex);
	startIndex = result3.second;

	std::string arg1 = result1.first;
	std::list<std::string> arg2 = result2.first;
	bool arg3 = result3.first;

	//                                          vvvvvvvvvvvvvvvvvvv this is why we don't take four arguments for the animation command
	AnimationManager::LoadAnimation(arg1, arg2, ANIMATION_FRAMERATE, arg3);
}

void AssetLoader::ParseGridCommand(std::string line)
{
	int startIndex = AssetLoader::COMMAND_GRID.size() + 1;

	std::pair<std::string, int> result1;
	std::pair<std::string, int> result2;

	result1 = TextParser::ParseForString(line, startIndex);
	startIndex = result1.second;
	
	result2 = TextParser::ParseForString(line, startIndex);
	startIndex = result2.second;

	std::string arg1 = result1.first;
	std::string arg2 = result2.first;

	MapManager::LoadMap(arg1, arg2);
}
