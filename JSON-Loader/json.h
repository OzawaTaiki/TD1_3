#pragma once
#include <string>
#include <variant>
#include <unordered_map>
#include <assert.h>

class JsonL
{
private:
	void	Load(const char* _path);
	std::unordered_map<std::string, std::string> data;

public:

	std::string operator[] (const char* key) const
	{
		auto it = data.find(key);
		if (it != data.end()) return it->second;
		else return {};
	}
	std::unordered_map<std::string, std::string>* rowData = &data;

	JsonL(const char* _path);
};

