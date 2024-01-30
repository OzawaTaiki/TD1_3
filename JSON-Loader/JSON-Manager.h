#pragma once
#include "json.h"
#include <vector>
#include <string>

class JSON_Manager
{
public:
	static	void	LoadJSON(const char* _name, const char* _path);
	static	JsonL*	GetJSON(const char* _jsonName);

private:
	static	std::vector<std::string> jsonNames;
	static	std::vector<JsonL> Jsons;
};