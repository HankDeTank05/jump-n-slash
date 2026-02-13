#include "JsonNodeStr.h"

JsonNodeStr::JsonNodeStr(std::string key, std::string _val)
	: JsonNodeBase(key),
	val(_val)
{
	// do nothing
}

void JsonNodeStr::SetValue(std::string _val)
{
	val = _val;
}

std::string JsonNodeStr::GetStrValue()
{
	return val;
}

void JsonNodeStr::AddChild(JsonNodeBase* pChild)
{
	assert(false); // do nothing. this function is not used.
}

std::list<JsonNodeBase*>& JsonNodeStr::GetListValue()
{
	assert(false); // do nothing. this function is not used
	std::list<JsonNodeBase*> list;
	return list;
}

void JsonNodeStr::SetValue(int val)
{
	assert(false); // do nothing. this function is not used.
}

int JsonNodeStr::GetIntValue()
{
	assert(false); // do nothing. this function is not used.
	return 0;
}
