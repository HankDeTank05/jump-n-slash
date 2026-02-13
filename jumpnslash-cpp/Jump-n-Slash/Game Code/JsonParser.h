#ifndef JSON_PARSER_H
#define JSON_PARSER_H

// forward declarations
class JsonNodeList;

class JsonParser
{
public:
	JsonParser() = default;
	JsonParser(const JsonParser& jr) = delete;
	JsonParser& operator=(const JsonParser& jr) = delete;
	virtual ~JsonParser() = default;

	void ReadJsonFile(std::string path);
};

#endif