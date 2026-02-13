#include "JsonNodeBase.h"

JsonNodeBase::JsonNodeBase(std::string _key)
	: key(_key),
	pParentNode(nullptr)
{
	// do nothing
}

std::string JsonNodeBase::GetKey()
{
	return key;
}

void JsonNodeBase::SetParentNode(JsonNodeBase* _pParentNode)
{
	assert(_pParentNode != nullptr);
	pParentNode = _pParentNode;
}

JsonNodeBase* JsonNodeBase::GetParentNode()
{
	return pParentNode;
}
