#pragma once
#include <vector>

class Piece;
class Player;

class Playground
{
	const int kMaxStage = 3;

	std::vector<std::vector<int>>* field;
	std::vector<std::vector<int>>* collision;

	int selectStage;
	bool isNext;
	bool isClear;



	const unsigned int kTileColor_[4] = {
		0xc5edbeff,
		0x000000ff,
		0xff0000ff,
		0x00ff00ff
	};

	//ファイル名一括管理 すべてここに入力
	const char* stageFilePath[64] = {
		"./data/testStage.csv"
	};

	Piece* piece;
	Player* player;

	/// 仮の者たち
	int blockTexture;
	int goalTexture;
	int obstacleTexture;


public:
	Playground();

	void Init(int _stageNo);
	void Update(const char* _keys, const char* _preKeys);
	void Draw();
};