#include "JSON-Manager.h"
#include <unordered_map>

std::vector<std::string> JSON_Manager::jsonNames;
std::vector<std::string> JSON_Manager::paths;
std::vector<JsonL> JSON_Manager::Jsons;

void JSON_Manager::LoadJSON(const char* _name, const char* _path)
{
	jsonNames.push_back(_name);
	paths.push_back(_path);
	Jsons.push_back(JsonL(_path));
}

void JSON_Manager::ReloadJSON(const char* _name)
{
	int index{};
	for (auto& elm : jsonNames)
	{
		if (strcmp(elm.c_str(), _name) == 0) break;
		index++;
	}
	if (index == jsonNames.size())
	{
		assert(index == jsonNames.size());
		return;
	}
	
	std::string path = paths[index].c_str();

	jsonNames.erase(jsonNames.begin() + index);
	paths.erase(paths.begin() + index);
	Jsons.erase(Jsons.begin() + index);

	LoadJSON(_name, path.c_str());
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
