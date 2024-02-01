#pragma once
#include <vector>
#include <Vector2.h>

class Piece;
class Player;
class Box;

class Playground
{
	const int kMaxStage = 10;

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
		"./data/stage1.csv",
		"./data/stage2.csv",
		"./data/stage3.csv",
		"./data/stage4.csv",
		"./data/stage5.csv",
		"./data/stage6.csv",
		"./data/stage7.csv",
		"./data/stage8.csv",
		"./data/stage9.csv",
		"./data/stage10.csv"
	};

	Piece* piece;
	Player* player;
	std::vector<Box*> box;


	/// 仮の者たち
	int blockTexture;
	int goalTexture;
	int obstacleTexture;

	bool frameSlow = false;

	bool isFill(const Vector2& _pos, const Vector2* _vertex);


	void GoalCheck();
	void SpineHitCheck();

	void CollisionWithPlayer();			//player	field
	void CollisionPlayerWithBox();		//player	box
	void CollisionPlayerWithPiece();	//player	piece

	void CollisionWithBox();			//box		field
	void CollisionPieceWithBox();		//box		piece
	void CollisionBoxWithBox();			//box		box

	/// お邪魔との判定とりたい関数 piece field
	void CollisionWithPiece();

	void CollisionReset();

	/*void PiecePlayerCollision();
	void BoxPieceCollision();
	void BoxBoxCollision();*/


public:
	Playground();

	void Init(int _stageNo);
	void Update(const char* _keys, const char* _preKeys);
	void Draw();
};