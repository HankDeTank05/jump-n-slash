#include "JsonNodeValue.h"

JsonNodeValue::JsonNodeValue(std::string key)
    : JsonNode(key),
    value("")
{
    // do nothing
}

JsonNodeValue::JsonNodeValue(std::string key, std::string _value)
    : JsonNode(key),
    value(_value)
{
    // do nothing
}

std::string JsonNodeValue::GetKey()
{
    return key;
}

std::string JsonNodeValue::GetValue()
{
    return value;
}

void JsonNodeValue::SetValue(std::string _value)
{
    value = _value;
}
