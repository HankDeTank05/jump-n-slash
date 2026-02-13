#ifndef ASSET_LOADER_H
#define ASSET_LOADER_H

// language includes
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
	void ParseGridCommand(std::string line);


private:
	static const std::string COMMAND_TEXTURE;
	static const std::string COMMAND_SPRITE;
	static const std::string COMMAND_ANIMATION;
	static const std::string COMMAND_GRID;

private:
	std::map<std::string, std::list<std::string>> commands;
	std::map<std::string, std::string> texturesToLoad;
};

#endif