#ifndef JSON_NODE_VALUE_H
#define JSON_NODE_VALUE_H

// language includes
#include <string>

// game includes
#include "JsonNode.h"

class JsonNodeValue : public JsonNode
{
public:
	JsonNodeValue() = delete;
	JsonNodeValue(std::string key);
	JsonNodeValue(std::string key, std::string value);
	JsonNodeValue(const JsonNodeValue& jnv) = delete;
	JsonNodeValue& operator=(const JsonNodeValue& jnv) = delete;
	virtual ~JsonNodeValue() = default;

	virtual std::string GetKey() override final;
	std::string GetValue();

	void SetValue(std::string value);

private:
	std::string value;
};

#endif