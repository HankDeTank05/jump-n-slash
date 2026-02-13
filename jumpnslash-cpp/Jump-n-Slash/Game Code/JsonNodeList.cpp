#include "JsonNodeList.h"

JsonNodeList::JsonNodeList(std::string key)
	: JsonNodeBase(key),
	children()
{
	// do nothing
}

JsonNodeList::~JsonNodeList()
{
	children.clear();
}

void JsonNodeList::AddChild(JsonNodeBase* pChild)
{
	children.push_back(pChild);
}

std::list<JsonNodeBase*>& JsonNodeList::GetListValue()
{
	return children;
}

void JsonNodeList::SetValue(std::string val)
{
	assert(false); // do nothing. this function is not used.
}

std::string JsonNodeList::GetStrValue()
{
	assert(false); // do nothing. this function is not used.
	return std::string();
}

void JsonNodeList::SetValue(int val)
{
	assert(false); // do nothing. this function is not used.
}

int JsonNodeList::GetIntValue()
{
	assert(false); // do nothing. this function is not used.
	return 0;
}
