#include "JsonParser.h"

// language includes
#include <iostream>
#include <fstream>
#include <vector>

// engine includes
#include "../Engine Code/ConvenienceFunctions.h"

// game includes
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
	// kvLines[i].second = (true = sublist, false = value)
	std::vector<std::pair<int, bool>> kvLines;

	// step 1: parse the json file for important data, line by line
	while (std::getline(jsonFile, line))
	{
		// parse a line of the file

		int strIndex = 0;
		std::string currentChar = line.substr(strIndex, strIndex + 1);

		// step 1.1: check the indent level for a hint on how nested this line is
		
		int indentLevel = 0;
		while (currentChar == "\t")
		{
			indentLevel++;
			strIndex++;
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
			// get the type of the value (either string or sublist)
			std::string valueChar = line.substr(colonPos + 2, 1);

			// check if value type is string
			if (valueChar == "\"")
			{
				kvLines.push_back(std::pair<int, bool>(lineNum, false));
			}
			// check if value type is sublist
			else if (valueChar == "{")
			{
				kvLines.push_back(std::pair<int, bool>(lineNum, true));
			}
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

	// step 2: determine max indent level

	int maxIndentLv = 0;
	for (int i = 0; i < indents.size(); i++)
	{
		if (indents[i] > maxIndentLv)
		{
			maxIndentLv = indents[i];
		}
	}

	std::cout << "Done parsing json file" << std::endl;
}
