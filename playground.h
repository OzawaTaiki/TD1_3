#pragma once
#include <vector>

class Playground
{
	const int kMaxStage = 3;

	std::vector<std::vector<int>>* field;
	std::vector<std::vector<int>>* collision;

	int selectStage;
	bool isNext;
	bool isClear;

	//ファイル名一括管理 すべてここに入力
	const char* stageFilePath[64] = {
		"testStage.csv"
	};

public:
	Playground();

	void Init(int _stageNo);

	void Draw();
};