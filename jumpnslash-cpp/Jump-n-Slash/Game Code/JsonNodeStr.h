#ifndef JSON_NODE_STR_H
#define JSON_NODE_STR_H

#include "JsonNodeBase.h"

class JsonNodeStr : public JsonNodeBase
{
public:
	JsonNodeStr() = delete;
	JsonNodeStr(std::string key, std::string val);
	JsonNodeStr(const JsonNodeStr& jns) = delete;
	JsonNodeStr& operator=(const JsonNodeStr& jns) = delete;
	virtual ~JsonNodeStr() = default;

	virtual void SetValue(std::string val) override;
	virtual std::string GetStrValue() override;

private:
	virtual void AddChild(JsonNodeBase* pChild) override;
	virtual std::list<JsonNodeBase*>& GetListValue() override;

	virtual void SetValue(int val) override;
	virtual int GetIntValue() override;

private:
	std::string val;
};

#endif