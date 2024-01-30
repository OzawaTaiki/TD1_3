#include "JSON-Manager.h"
#include <unordered_map>

std::unordered_map<std::string, JsonL> JSON_Manager::jsonMap;

void JSON_Manager::LoadJSON(const char* _name, const char* _path)
{
	JsonL json(_path);
	jsonMap[_name] = json;
}

JsonL* JSON_Manager::GetJSON(const char* _jsonName)
{
	return &jsonMap[_jsonName];
}
