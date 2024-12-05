#ifndef JSON_NODE_BASE_H
#define JSON_NODE_BASE_H

// language includes
#include <string>
#include <list>

class JsonNodeBase
{
public:
	JsonNodeBase() = delete;
	JsonNodeBase(std::string key);
	JsonNodeBase(const JsonNodeBase& jnb) = delete;
	JsonNodeBase& operator=(const JsonNodeBase& jnb) = delete;
	virtual ~JsonNodeBase() = default;

	std::string GetKey();

	void SetParentNode(JsonNodeBase* pParentNode);
	JsonNodeBase* GetParentNode();

	virtual void AddChild(JsonNodeBase* pChild) = 0;
	virtual std::list<JsonNodeBase*>& GetListValue() = 0;
	
	virtual void SetValue(std::string val) = 0;
	virtual std::string GetStrValue() = 0;
	
	virtual void SetValue(int val) = 0;
	virtual int GetIntValue() = 0;

	

protected:
	JsonNodeBase* pParentNode;
	std::string key;
};

#endif