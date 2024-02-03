#pragma once
#include "json.h"
#include <vector>
#include <string>

class JSON_Manager
{
public:
	static	void	LoadJSON(const char* _name, const char* _path);
	static	void	ReloadJSON(const char* _name);
	static	JsonL*	GetJSON(const char* _jsonName);

private:
	static	std::vector<std::string> jsonNames;
	static	std::vector<std::string> paths;
	static	std::vector<JsonL> Jsons;
};