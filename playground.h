#pragma once
#include <vector>
#include <Vector2.h>
#include "intVec2.h"
#include "JSON-Loader/JSON-Manager.h"
#include "UI/UI_Manager.h"
#include "sound.h"
#include "FillWPlayer.h"

class Piece;
class Player;
class Box;

class Playground
{
	const int kMaxStage = 8;

	std::vector<std::vector<int>>* field;

	std::vector<intVec2> hindrancePos;
	Vector2 hindranceVertex[4];

	int selectStage;
	bool isNext;
	bool isClear;

	bool plbo;
	bool plpi;
	bool pibo;

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

	/// - - - ナイトウが勝手に宣言 はじめ - - - ///

	JsonL* json_scr;

	SpriteData	scrSpr;					// スクロールバーのリソース
	Scroller* scrollBar;              // スクロールバー実体

	Size		scrollBarSize;          // スクロールバーのサイズ
	Size		scrollboxSize;          // スクロールボックスのサイズ
	int			scrollboxMargin;
	Transform	scrollbarPosition;
	int			scrollMarginTop;        // スクロール要素 上マージン
	int			increaseY_scroll;		// スクロールによるy増加分（マイナス値へ変化する）
	FillWithPlayer* fwp;
	int			isChangetm;

	int			tabHandle;
	/// - - -  ナイトウが勝手に宣言 おわり - - - ///

	int blockTexture;
	int goalTexture;
	//int obstacleTexture;
	int backGroundTexture;
	int togeTexture;

	Sound* BGM;
	Sound* goalSound;


	bool frameSlow = false;


	bool isFill(const Vector2& _pos, const Vector2* _vertex);


	void GoalCheck();
	void SpineHitCheck();

	void CollisionWithPlayer();			//player	field
	void CollisionPlayerWithBox();		//player	box
	void CollisionPlayerWithPiece();	//player	piece

	void CollisionWithBox();			//box		field
	void CollisionPieceWithBox();		//box		piece

	void CollisionWithPiece();
	void CollisionPieceWithPiece();


	void LoadFromJSON();
	void ScrollCalculation();
public:
	Playground();

	void Init(int _stageNo);
	void Update(const char* _keys, const char* _preKeys);
	void Draw();
	static	int	allClear;
};