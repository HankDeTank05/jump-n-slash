#include "JsonNodeList.h"

JsonNodeList::JsonNodeList(std::string key)
	: JsonNode(key),
	subnodes()
{
	// do nothing
}

JsonNodeList::JsonNodeList(std::string key, std::list<JsonNode*> _subnodes)
	: JsonNode(key),
	subnodes(_subnodes)
{
	// do nothing
}

JsonNodeList::~JsonNodeList()
{
	subnodes.clear();
}

std::string JsonNodeList::GetKey()
{
	return key;
}

std::list<JsonNode*> JsonNodeList::GetSubnodes()
{
	return subnodes;
}

void JsonNodeList::AddSubnode(JsonNode* pNode)
{
	assert(pNode != nullptr);
	subnodes.push_back(pNode);
}
