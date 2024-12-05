#ifndef TILESET_H
#define TILESET_H

// language includes
#include <map>
#include <string>

// forward declarations
class JsonNodeList;
class Sprite;

class Tileset
{
public:
	Tileset() = delete;
	Tileset(JsonNodeList* pNodeList);
	Tileset(const Tileset& t) = delete;
	Tileset& operator=(const Tileset& t) = delete;
	virtual ~Tileset() = default;

private:
	std::map<std::string, Sprite*> legend;
};

#endif