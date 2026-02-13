#ifndef TEXT_PARSER_H
#define TEXT_PARSER_H

// language includes
#include <map>
#include <list>

class TextParser
{
public:
	TextParser() = default;
	TextParser(const TextParser& tp) = delete;
	TextParser& operator=(const TextParser& tp) = delete;
	virtual ~TextParser() = default;

	static std::pair<std::string, int> ParseForString(std::string line, int startIndex);
	static std::pair<float, int> ParseForFloat(std::string line, int startIndex);
	static std::pair<int, int> ParseForInt(std::string line, int startIndex);
	static std::pair<bool, int> ParseForBool(std::string line, int startIndex);
	static std::pair<std::list<std::string>, int> ParseForListString(std::string line, int startIndex);

	static const std::string TYPE_STRING;
	static const std::string TYPE_FLOAT;
	static const std::string TYPE_INT;
	static const std::string TYPE_BOOL;
	static const std::string TYPE_LIST_STRING;
	static const std::string TYPE_LIST_FLOAT;
	static const std::string TYPE_LIST_INT;
	static const std::string TYPE_LIST_BOOL;
};

#endif