#ifndef JSON_PARSER_H
#define JSON_PARSER_H

// forward declarations
class JsonNodeList;

class JsonParser
{
public:
	JsonParser();
	JsonParser(const JsonParser& jr) = delete;
	JsonParser& operator=(const JsonParser& jr) = delete;
	virtual ~JsonParser();

	void ReadJsonFile(std::string path);
	JsonNodeList* GetData();

private:
	JsonNodeList* pHead;
};

#endif