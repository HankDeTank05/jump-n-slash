#ifndef JSON_NODE_H
#define JSON_NODE_H

// language includes
#include <string>

class JsonNode
{
public:
	JsonNode() = delete;
	JsonNode(std::string key);
	JsonNode(const JsonNode& jn) = delete;
	JsonNode& operator=(const JsonNode& jn) = delete;
	virtual ~JsonNode() = default;

	virtual std::string GetKey() = 0;

protected:
	std::string key;
};

#endif