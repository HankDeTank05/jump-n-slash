#include "AssetLoader2.h"

// language includes
#include <fstream>
#include <iostream>

// library includes
#include "nlohmann/json.hpp"

// game includes
#include "AssetLoadCommand.h"
#include "TextureLoadCommand.h"
#include "SpriteLoadCommand.h"

const std::string AssetLoader2::SECTION_TEXTURES = "textures";
const std::string AssetLoader2::SECTION_SPRITES = "sprites";
const std::string AssetLoader2::SECTION_ANIMATIONS = "animations";
const std::string AssetLoader2::SECTION_LEVELDATA = "leveldata";

void AssetLoader2::ReadAssetSetupFile()
{
	std::ifstream assetSetupFile("assets/assetSetupFile_2.json");
	json data = json::parse(assetSetupFile);
    //PrintJson(data);
    GenerateLoadInstructions(data);
}

void AssetLoader2::LoadAssets()
{
    while (instructions.empty() == false)
    {
        AssetLoadCommand* pCmd = instructions.front();
        instructions.pop();

        pCmd->Execute();
        delete pCmd;
    }
}

void AssetLoader2::GenerateLoadInstructions(json data)
{
    // read texture data

    json textureData = data.at(AssetLoader2::SECTION_TEXTURES);
    //PrintJson(textureData);
    assert(textureData.is_array() == true); // sanity check

    // iterate over each texture entry in the list and generate a command for each one
    for (json::iterator it = textureData.begin(); it != textureData.end(); it++)
    {
        assert((*it).is_object() == true); // sanity check

        // access values
        std::string key = (*it).at("key"); // TODO: make this key a static constant
        std::string filename = (*it).at("path"); // TODO: make this key a static constant
        bool smooth = (*it).at("smooth"); // TODO: make this key a static constant

        // generate a command to be executed later
        instructions.push(new TextureLoadCommand(key, filename, smooth));
    }

    // read sprite data

    json spriteData = data.at(AssetLoader2::SECTION_SPRITES);
    //PrintJson(spriteData);
    assert(spriteData.is_array() == true);

    // iterate over each sprite entry in the list and generate a command for each one
    for (json::iterator it = spriteData.begin(); it != spriteData.end(); it++)
    {
        assert((*it).is_object() == true); // sanity check

        // access values
        std::string sprKey = (*it).at("sprKey"); // TODO: make this key a static constant
        std::string texKey = (*it).at("texKey"); // TODO: make this key a static constant
        int x = (*it).at("x"); // TODO: make this key a static constant
        int y = (*it).at("y"); // TODO: make this key a static constant
        int w = (*it).at("w"); // TODO: make this key a static constant
        int h = (*it).at("h"); // TODO: make this key a static constant

        // TODO: generate a command to be executed later
        instructions.push(new SpriteLoadCommand(sprKey, texKey, x, y, w, h));
    }

    // TODO: read animation data

    // TODO: read level data

    //assert(false);
}

void AssetLoader2::PrintJson(json data, int indent)
{
    for (json::iterator it = data.begin(); it != data.end(); it++)
    {
        // print whitespace (indent)
        PrintTabs(indent);

        // print key (only if not printing a list)
        if (data.is_array() == false)
        {
            std::cout << it.key() << " : ";
        }

        // print the value
        if ((*it).is_array() == true)
        {
            std::cout << "[" << std::endl;

            PrintJson(*it, indent + 1);

            PrintTabs(indent);
            std::cout << "],";
        }
        else if ((*it).is_object() == true)
        {
            std::cout << "{" << std::endl;

            PrintJson(*it, indent + 1);

            PrintTabs(indent);
            std::cout << "},";
        }
        else
        {
            std::cout << it.value();
        }

        // print newline character
        std::cout << std::endl;
    }
}

void AssetLoader2::PrintTabs(int tabs)
{
	for (int i = 0; i < tabs; i++)
	{
		std::cout << "\t";
	}
}
