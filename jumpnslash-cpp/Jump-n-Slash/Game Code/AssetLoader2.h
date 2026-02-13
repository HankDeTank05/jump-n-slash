#ifndef ASSET_LOADER_2
#define ASSET_LOADER_2

// language includes
#include <queue>

// library includes
#include "nlohmann/json_fwd.hpp"
using json = nlohmann::json;

// forward declarations
class AssetLoadCommand;

class AssetLoader2
{
public:
	AssetLoader2() = default;
	AssetLoader2(const AssetLoader2& al2) = delete;
	AssetLoader2& operator=(const AssetLoader2& al2) = delete;
	virtual ~AssetLoader2() = default;

	void ReadAssetSetupFile();
	void LoadAssets();

private:
	void GenerateLoadInstructions(json data);
	void PrintJson(json data, int indent = 0);
	void PrintTabs(int tabs);

private:
	std::queue<AssetLoadCommand*> instructions;

private:
	static const std::string SECTION_TEXTURES;
	static const std::string SECTION_SPRITES;
	static const std::string SECTION_ANIMATIONS;
	static const std::string SECTION_LEVELDATA;
};

#endif