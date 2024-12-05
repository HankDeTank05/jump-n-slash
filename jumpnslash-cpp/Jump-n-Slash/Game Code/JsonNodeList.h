#ifndef JSON_NODE_LIST_H
#define JSON_NODE_LIST_H

#include "JsonNodeBase.h"

class JsonNodeList : public JsonNodeBase
{
public:
	JsonNodeList() = delete;
	JsonNodeList(std::string key);
	JsonNodeList(const JsonNodeList& jnl) = delete;
	JsonNodeList& operator=(const JsonNodeList& jnl) = delete;
	virtual ~JsonNodeList();

	virtual void AddChild(JsonNodeBase* pChild) override;
	virtual std::list<JsonNodeBase*>& GetListValue() override;

private:
	virtual void SetValue(std::string val) override;
	virtual std::string GetStrValue() override;

	virtual void SetValue(int val) override;
	virtual int GetIntValue() override;

private:
	std::list<JsonNodeBase*> children;
};

#endif