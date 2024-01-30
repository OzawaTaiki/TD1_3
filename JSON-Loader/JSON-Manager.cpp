#include "JSON-Manager.h"
#include <unordered_map>

std::vector<std::string> JSON_Manager::jsonNames;
std::vector<JsonL> JSON_Manager::Jsons;

void JSON_Manager::LoadJSON(const char* _name, const char* _path)
{
	jsonNames.push_back(_name);
	Jsons.push_back(JsonL(_path));
}

JsonL* JSON_Manager::GetJSON(const char* _jsonName)
{
	int index{};
	for (auto& elm : jsonNames)
	{
		if (strcmp(elm.c_str(), _jsonName) == 0) break;
		index++;
	}
	return &Jsons[index];
}
