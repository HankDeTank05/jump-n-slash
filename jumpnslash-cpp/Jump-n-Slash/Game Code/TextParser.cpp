#include "TextParser.h"

const std::string TextParser::TYPE_STRING = "string";
const std::string TextParser::TYPE_FLOAT = "float";
const std::string TextParser::TYPE_INT = "int";
const std::string TextParser::TYPE_BOOL = "bool";
const std::string TextParser::TYPE_LIST_STRING = "list<" + TextParser::TYPE_STRING + ">";
const std::string TextParser::TYPE_LIST_FLOAT = "list<" + TextParser::TYPE_FLOAT + ">";
const std::string TextParser::TYPE_LIST_INT = "list<" + TextParser::TYPE_INT + ">";
const std::string TextParser::TYPE_LIST_BOOL = "list<" + TextParser::TYPE_BOOL + ">";

std::pair<std::string, int> TextParser::ParseForString(std::string line, int startIndex)
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

std::pair<int, int> TextParser::ParseForInt(std::string line, int startIndex)
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
	return std::pair<int, int>(parsedInt, currentIndex); // return the parsed int and the new starting index
}

std::pair<bool, int> TextParser::ParseForBool(std::string line, int startIndex)
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

	return std::pair<bool, int>(parsedBool, currentIndex); // return the parsed bool and the new starting index
}

std::pair<std::list<std::string>, int> TextParser::ParseForListString(std::string line, int startIndex)
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
		else if (listStartIndex > -1 && currentChar != "]")
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

	return std::pair<std::list<std::string>, int>(spriteKeyList, currentIndex + 1); // return the parsed string list and the new starting index
}
