#include "Tileset.h"

// game includes
#include "JsonNodeList.h"

Tileset::Tileset(JsonNodeList* pNodeList)
	: legend()
{
	assert(pNodeList->GetKey() == "decodeTiles"); // TODO: this string is hard coded and "that's NO GOOD"
	std::list<JsonNodeBase*> decodeList = pNodeList->GetListValue();
	for (std::list<JsonNodeBase*>::iterator it = decodeList.begin(); it != decodeList.end(); it++)
	{
		std::string levelDataID = (*it)->GetKey();
		std::string filename = (*it)->GetStrValue();
	}
}
