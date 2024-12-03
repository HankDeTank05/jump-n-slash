#ifndef JSON_NODE_LIST_H
#define JSON_NODE_LIST_H

// language includes
#include <string>
#include <list>

// game includes
#include "JsonNode.h"

class JsonNodeList : public JsonNode
{
public:
	JsonNodeList() = delete;
	JsonNodeList(std::string key);
	JsonNodeList(std::string key, std::list<JsonNode*> subnodes);
	JsonNodeList(const JsonNodeList& jnl) = delete;
	JsonNodeList& operator=(const JsonNodeList& jnl) = delete;
	virtual ~JsonNodeList();

	virtual std::string GetKey() override final;
	std::list<JsonNode*> GetSubnodes();

	void AddSubnode(JsonNode* pNode);

private:
	std::list<JsonNode*> subnodes;
};

#endif