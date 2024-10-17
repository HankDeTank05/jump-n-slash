#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

#include <map>
#include <list>

class AssetLoader
{
public:
	AssetLoader();
	AssetLoader(const AssetLoader& al) = delete;
	AssetLoader& operator=(const AssetLoader& al) = delete;
	virtual ~AssetLoader();

	void ReadAssetSetupFile();

private:
	void ParseCommand(std::string line, std::string command);
	void ParseTextureCommand(std::string line);
	void ParseSpriteCommand(std::string line);
	void ParseAnimationCommand(std::string line);

	std::pair<std::string, int> ParseForString(std::string line, int startIndex);
	std::pair<float, int> ParseForFloat(std::string line, int startIndex);
	std::pair<int, int> ParseForInt(std::string line, int startIndex);
	std::pair<bool, int> ParseForBool(std::string line, int startIndex);
	std::pair<std::list<std::string>, int> ParseForListString(std::string line, int startIndex);


private:
	static const std::string COMMAND_TEXTURE;
	static const std::string COMMAND_SPRITE;
	static const std::string COMMAND_ANIMATION;

	static const std::string TYPE_STRING;
	static const std::string TYPE_FLOAT;
	static const std::string TYPE_INT;
	static const std::string TYPE_BOOL;
	static const std::string TYPE_LIST_STRING;
	static const std::string TYPE_LIST_FLOAT;
	static const std::string TYPE_LIST_INT;
	static const std::string TYPE_LIST_BOOL;

private:
	std::map<std::string, std::list<std::string>> commands;
	std::map<std::string, std::string> texturesToLoad;
};

#endif