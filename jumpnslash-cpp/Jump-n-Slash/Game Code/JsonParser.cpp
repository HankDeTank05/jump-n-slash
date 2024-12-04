#include "JsonParser.h"

// language includes
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

// engine includes
#include "../Engine Code/ConvenienceFunctions.h"

// game includes
#include "JsonNode.h"
#include "JsonNodeList.h"
#include "JsonNodeValue.h"

JsonParser::JsonParser()
	: pHead(new JsonNodeList("json file"))
{
	// do nothing
}

JsonParser::~JsonParser()
{
	delete pHead;
}

void JsonParser::ReadJsonFile(std::string path)
{
	// parse a json file

	int lineNum = 0;
	std::string line;

	std::ifstream jsonFile(path);

	// index = line number
	// indentLevel[index] = indent level
	std::vector<int> indents;

	// braces[i].first = line number
	// braces[i].second = (true = open, false = close)
	std::vector<std::pair<int, bool>> braces;

	// kvLines[i].first = line number
	// kvLines[i].second.first = key
	// kvLines[i].second.second = (true = sublist, false = value)
	std::vector<std::pair<int, std::pair<std::string, bool>>> kvLines;

	// step 1: parse the json file for important data, line by line
	while (std::getline(jsonFile, line))
	{
		// parse a line of the file

		int strIndex = 0;
		std::string currentChar = line.substr(strIndex, 1);

		// step 1.1: check the indent level for a hint on how nested this line is
		
		int indentLevel = 0;
		int spaces = 0;
		while (currentChar == " ")
		{
			spaces++;
			if (spaces % 4 == 0)
			{
				indentLevel++;
			}
			strIndex++;
			currentChar = line.substr(strIndex, 1);
		}
		indents.push_back(indentLevel);

		// step 1.2: check for opening or closing curly braces

		if (line.find("{") != std::string::npos)
		{
			braces.push_back(std::pair<int, bool>(lineNum, true));
		}
		else if (line.find("}") != std::string::npos)
		{
			braces.push_back(std::pair<int, bool>(lineNum, false));
		}

		// step 1.3: check for lines where key/value pairs are defined

		size_t colonPos = line.find(":");
		if (colonPos != std::string::npos)
		{
			// get the key on this line
			size_t keyStartPos = colonPos - 2; // colonPos - 1 should be the index of the closing double-quote
			int keyLen = 1;

			// sanity check to make sure colons are always preceded by a closing double-quote
			assert(line.substr(colonPos - 1, 1) == "\""); 

			// iterate backwards until you find the opening quote
			while (line.substr(keyStartPos - 1, 1) != "\"")
			{
				keyStartPos--;
				keyLen++;
			}

			// sanity check to make sure keyStartPos is the index of the first letter of the key, not the index of the opening double-quote
			assert(line.substr(keyStartPos - 1, 1) == "\""); 

			std::string key = line.substr(keyStartPos, keyLen);

			// get the type of the value (either string or sublist)
			std::string valueChar = line.substr(colonPos + 2, 1);

			// check if value type is string
			if (valueChar == "\"")
			{
				kvLines.push_back(std::pair<int, std::pair<std::string, bool>>(lineNum, std::pair<std::string, bool>(key, false)));
			}
			// check if value type is sublist
			else if (valueChar == "{")
			{
				kvLines.push_back(std::pair<int, std::pair<std::string, bool>>(lineNum, std::pair<std::string, bool>(key, true)));
			}
			// check if value type is an integer
			else if (std::stoi(valueChar))
			{
				// do nothing yet (but if you get here, you know the value is a number)
				assert(true);
			}
			else
			{
				assert(false);
			}
		}

		// last step
		lineNum++;
	}
	assert(lineNum == indents.size());

	// step 2: create data structure and populate with json data

	// step 2.1: determine max indent level

	int maxIndentLv = 0;
	for (int i = 0; i < indents.size(); i++)
	{
		if (indents[i] > maxIndentLv)
		{
			maxIndentLv = indents[i];
		}
	}

	std::queue<std::pair<int, JsonNodeList*>> q;
	for (int currIndentLv = 1; currIndentLv <= maxIndentLv; currIndentLv++)
	{
		for (int i = 0; i < kvLines.size(); i++)
		{
			lineNum = kvLines[i].first;
			bool hasSublist = kvLines[i].second.second;
			int lineIndent = indents[lineNum];
			if (lineIndent == currIndentLv && hasSublist == true);
			{
				assert(lineIndent == currIndentLv);
				assert(hasSublist == true);
				std::string key = kvLines[i].second.first;
				JsonNodeList* pListNode = new JsonNodeList(key);
				q.push(std::pair<int, JsonNodeList*>(lineNum, pListNode));
			}
		}
	}

	std::cout << "Done parsing json file" << std::endl;
}
