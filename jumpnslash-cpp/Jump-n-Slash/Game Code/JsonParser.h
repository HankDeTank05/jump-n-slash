#ifndef JSON_PARSER_H
#define JSON_PARSER_H

class JsonParser
{
public:
	static void ParseJson(std::string filename);
	static void LoadSpritesFromJson();
};

#endif