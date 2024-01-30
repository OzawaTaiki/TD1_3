#pragma once
#include "json.h"
#include <unordered_map>
#include <string>

class JSON_Manager
{
public:
	static	void	LoadJSON(const char* _name, const char* _path);
	static	JsonL*	GetJSON(const char* _jsonName);

private:
	static	std::unordered_map<std::string, JsonL> jsonMap;
};