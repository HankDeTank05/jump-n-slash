#include "AssetLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>

#include "../Engine Code/TextureManager.h"
#include "../Engine Code/SpriteManager.h"
#include "../Engine Code/AnimationManager.h"

#include "Constants.h"
#include "DesignerControls.h"

const std::string AssetLoader::COMMAND_TEXTURE = "texture";
const std::string AssetLoader::COMMAND_SPRITE = "sprite";
const std::string AssetLoader::COMMAND_ANIMATION = "animation";

const std::string AssetLoader::TYPE_STRING = "string";
const std::string AssetLoader::TYPE_FLOAT = "float";
const std::string AssetLoader::TYPE_INT = "int";
const std::string AssetLoader::TYPE_BOOL = "bool";
const std::string AssetLoader::TYPE_LIST_STRING = "list<" + AssetLoader::TYPE_STRING + ">";
const std::string AssetLoader::TYPE_LIST_FLOAT = "list<" + AssetLoader::TYPE_FLOAT + ">";
const std::string AssetLoader::TYPE_LIST_INT = "list<" + AssetLoader::TYPE_INT + ">";
const std::string AssetLoader::TYPE_LIST_BOOL = "list<" + AssetLoader::TYPE_BOOL + ">";


AssetLoader::AssetLoader()
	: commands(),
	texturesToLoad()
{
	// define the "texture" command

	std::list<std::string> textureArgs;
	textureArgs.push_back(AssetLoader::TYPE_STRING); // texture key
	textureArgs.push_back(AssetLoader::TYPE_STRING); // file name
	textureArgs.push_back(AssetLoader::TYPE_BOOL); // smooth
	commands.emplace(AssetLoader::COMMAND_TEXTURE, textureArgs);

	// define the "sprite" command

	std::list<std::string> spriteArgs;
	spriteArgs.push_back(AssetLoader::TYPE_STRING); // sprite key
	spriteArgs.push_back(AssetLoader::TYPE_STRING); // texture key
	spriteArgs.push_back(AssetLoader::TYPE_INT); // texture x origin
	spriteArgs.push_back(AssetLoader::TYPE_INT); // texture y origin
	spriteArgs.push_back(AssetLoader::TYPE_INT); // texture width
	spriteArgs.push_back(AssetLoader::TYPE_INT); // texture height
	commands.emplace(AssetLoader::COMMAND_SPRITE, spriteArgs);

	// define the "animation" command

	std::list<std::string> animArgs;
	animArgs.push_back(AssetLoader::TYPE_STRING); // animation key
	animArgs.push_back(AssetLoader::TYPE_LIST_STRING); // list of sprite keys
	// NOTE: there is no argument for animation fps here, since we set that in DesignerControls.h
	animArgs.push_back(AssetLoader::TYPE_BOOL); // loop flag
	commands.emplace(AssetLoader::COMMAND_ANIMATION, animArgs);
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

	while (std::getline(assetSetupFile, line))
	{
		int strIndex = 0;

		std::string command = "none";
		std::string currentChar = line.substr(0, 1);
		assert(currentChar != " "); // lines may not start with spaces!
		assert(currentChar != "\t"); // lines may not start with tab characters!

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

	// TODO: make a debug flag for this
	std::cout << "Successfully parsed the following asset command: " << line << std::endl;
}

void AssetLoader::ParseTextureCommand(std::string line)
{
	int startIndex = AssetLoader::COMMAND_TEXTURE.size() + 1;

	std::pair<std::string, int> result1;
	std::pair<std::string, int> result2;
	std::pair<bool, int> result3;

	result1 = ParseForString(line, startIndex);
	startIndex = result1.second;

	result2 = ParseForString(line, startIndex);
	startIndex = result2.second;

	result3 = ParseForBool(line, startIndex);

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

	result1 = ParseForString(line, startIndex);
	startIndex = result1.second;

	result2 = ParseForString(line, startIndex);
	startIndex = result2.second;

	result3 = ParseForInt(line, startIndex);
	startIndex = result3.second;

	result4 = ParseForInt(line, startIndex);
	startIndex = result4.second;

	result5 = ParseForInt(line, startIndex);
	startIndex = result5.second;

	result6 = ParseForInt(line, startIndex);
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

	result1 = ParseForString(line, startIndex);
	startIndex = result1.second;

	result2 = ParseForListString(line, startIndex);
	startIndex = result2.second;

	result3 = ParseForBool(line, startIndex);
	startIndex = result3.second;

	std::string arg1 = result1.first;
	std::list<std::string> arg2 = result2.first;
	bool arg3 = result3.first;

	//                                          vvvvvvvvvvvvvvvvvvv this is why we don't take four arguments for the animation command
	AnimationManager::LoadAnimation(arg1, arg2, ANIMATION_FRAMERATE, arg3);
}

std::pair<std::string, int> AssetLoader::ParseForString(std::string line, int startIndex)
{
	std::string parsedString = "none";

	int currentIndex = startIndex;

	int stringStartIndex = -1;
	int stringEndIndex = -1;

	while (stringEndIndex == -1 && currentIndex < line.size())
	{
		std::string currentChar = line.substr(currentIndex, 1);
		if (currentChar == "\"")
		{
			if (stringStartIndex == -1)
			{
				stringStartIndex = currentIndex + 1;
			}
			else if (stringEndIndex == -1)
			{
				assert(stringStartIndex > -1); // string start must already be set!
				stringEndIndex = currentIndex;
			}
			else
			{
				assert(false); // how tf...?
			}
		}
		currentIndex++;
	}
	assert(stringStartIndex > -1); // opening quotation mark was not found!
	assert(stringEndIndex > -1); // closing quotation mark was not found!
	assert(stringStartIndex < stringEndIndex); // idek how tf this could be triggered but sanity checks are always nice

	parsedString = line.substr(stringStartIndex, stringEndIndex - stringStartIndex);

	assert(parsedString != "none");
	return std::pair<std::string, int>(parsedString, currentIndex); // return the parsed string and the new starting index
}

std::pair<int, int> AssetLoader::ParseForInt(std::string line, int startIndex)
{
	int parsedInt;
	bool parseSuccessful = false;
	int currentIndex = startIndex;
	int numStartIndex = -1;
	int numEndIndex = -1;

	while (numEndIndex == -1 && currentIndex < line.size())
	{
		std::string currentChar = line.substr(currentIndex, 1);
		int charAsciiVal = static_cast<int>(currentChar[0]);
		if (48 <= charAsciiVal && charAsciiVal <= 57)
		{
			if (numStartIndex == -1)
			{
				numStartIndex = currentIndex;
			}
		}
		else
		{
			if ((numStartIndex > -1 && numEndIndex == -1) || currentIndex == line.size() - 1)
			{
				numEndIndex = currentIndex;
				//parseSuccessful = true;
			}
		}
		currentIndex++;
	}

	std::string intString = line.substr(numStartIndex, numEndIndex - numStartIndex);
	parsedInt = std::stoi(intString);

	//assert(parseSuccessful);
	return std::pair<int, int>(parsedInt, currentIndex);
}

std::pair<bool, int> AssetLoader::ParseForBool(std::string line, int startIndex)
{
	bool parseSuccessful = false;
	bool parsedBool;
	int currentIndex = startIndex;

	if (line.substr(startIndex, 4) == "true")
	{
		parseSuccessful = true;
		parsedBool = true;
		currentIndex += 4;
	}
	else if (line.substr(startIndex, 5) == "false")
	{
		parseSuccessful = true;
		parsedBool = false;
		currentIndex += 5;
	}

	assert(parseSuccessful == true); // unable to parse boolean value!

	return std::pair<bool, int>(parsedBool, currentIndex);
}

std::pair<std::list<std::string>, int> AssetLoader::ParseForListString(std::string line, int startIndex)
{
	int currentIndex = startIndex;

	int listStartIndex = -1;
	int listEndIndex = -1;

	std::list<std::string> spriteKeyList;

	while (listEndIndex == -1 && currentIndex < line.size())
	{
		std::string currentChar = line.substr(currentIndex, 1);
		if (listStartIndex == -1 && currentChar == "[")
		{
			listStartIndex = currentIndex;
			currentIndex++;
		}
		else if(listStartIndex > -1 && currentChar != "]")
		{
			std::pair<std::string, int> result = ParseForString(line, currentIndex);
			spriteKeyList.push_back(result.first);
			currentIndex = result.second;
		}
		else if (currentChar == "]")
		{
			assert(listStartIndex > -1);
			listEndIndex = currentIndex;
		}
	}

	return std::pair<std::list<std::string>, int>(spriteKeyList, currentIndex + 1);
}
