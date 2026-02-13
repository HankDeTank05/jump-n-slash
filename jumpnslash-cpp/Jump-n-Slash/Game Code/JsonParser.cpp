#include "JsonParser.h"

// language includes
#include <iostream>
#include <fstream>
#include <list>
#include <string>

// engine includes
#include "../Engine Code/ConvenienceFunctions.h"

// game includes
#include "JsonNodeBase.h"
#include "JsonNodeList.h"
#include "JsonNodeStr.h"

void JsonParser::ReadJsonFile(std::string path)
{
	// parse a json file

	int lineNum = 0;
	std::string line;

	std::ifstream jsonFile(path);

	JsonNodeBase* pParentNode = nullptr;

	int prevIndentLevel = -1;

	while (std::getline(jsonFile, line))
	{
		assert(pParentNode != nullptr);

		std::string currentChar;
		
		// determine indent level

		int strIndex = 0;
		int spaces = 0;
		int indentLevel = 0;
		currentChar = line.substr(strIndex, 1);
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

		// find the position of the colon

		size_t colonPos = line.find(":");
		if (colonPos != std::string::npos)
		{
			// find the key on this line

			size_t keyStartIndex = colonPos - 2;
			// minus 1: the closing quote for the key. minus 2: the last character of the key
			
			int keyLen = 1;

			// loop backwards (to the left) through the key until we reach the first character of the key
			while (line.substr(keyStartIndex - 1, 1) != "\"")
			{
				keyStartIndex--;
				keyLen++;
			}
			assert(line.substr(keyStartIndex - 1, 1) == "\""); // sanity check: make sure the character immediately to the left is the opening quote of the key
			std::string key = line.substr(keyStartIndex, keyLen); // create the key

			// find the value on this line

			size_t valStartIndex = colonPos + 2;
			// plus 1: space character following colon. plus 2: character to determine value type
			currentChar = line.substr(valStartIndex, 1);
			if (currentChar == "{")
			{
				assert(true); // value is a sub-map
				// TODO: determine value type (key type is string)
			}
			else if (currentChar == "[")
			{
				assert(true); // value is a list of some kind
				// TODO: determine element type
			}
			else if (currentChar == "\"")
			{
				// value is a string

				int valEndIndex = valStartIndex;
				while (line.substr(valEndIndex + 1, 1) != "\"")
				{
					valEndIndex++;
				}
				std::string val = line.substr(valStartIndex, valEndIndex + 1 - valStartIndex);
			}
			else if (currentChar == "t" || currentChar == "f")
			{
				assert(true); // value is a boolean
			}
			else if (currentChar == "0" || currentChar == "1" || currentChar == "2" || currentChar == "3" ||currentChar == "4" ||
				currentChar == "5" || currentChar == "6" || currentChar == "7" || currentChar == "8" || currentChar == "9")
			{
				assert(true); // value is a number
				// TODO: determine if it's int or float
			}
			else
			{
				assert(false); // value is of unknown type
			}
		}
		else if (lineNum > 0)
		{
			assert(line.find("}") != std::string::npos); // there must be a closing curly brace on any line that does not have a k/v pair (except for the first line)
			assert(indentLevel == prevIndentLevel - 1); // the indent level of the closing curly brace should be one less than prevIndentLevel

			// return to the previous parent node
			assert(pParentNode != nullptr);
			pParentNode = pParentNode->GetParentNode();
		}

		// prepare for the next run of the loop
		prevIndentLevel = indentLevel;
		lineNum++;
	}

	std::cout << "Done parsing json file" << std::endl;
}
