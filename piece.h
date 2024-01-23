#pragma once

#include <Vector2.h>
#include <vector>
#include "intVec2.h"

class Piece
{
	std::vector<std::vector<std::vector<int>>>* piece;
	std::vector<Vector2> piecePos;
	std::vector<Vector2> pieceSize;
	std::vector<intVec2> piecePosInMapchip;
	std::vector<float> scale;

	const float kKeyScale[2] = {
		1.0f,0.75f
	};

	/// 隣接部関連
	std::vector<intVec2> adjacentPos;		//ピースが隣接してるときの左or上の座標
	std::vector<char> adjacentDir;

	Vector2 p2mSub;							// マウスとpiecePosの差
	Vector2 piecePrePos;					// pieceの前の座標

	/// piece初期位置
	const Vector2 kPieceStartKeyPos = { 1500.0f,30.0f };			// pieceの初期基準座標
	const Vector2 kPieceStartMargin = { 0.0f,200.0f };				// pieceの初期位置間隔

	int isHave;								// piece所持フラグ -1:もってない 0~:番号のピース所持



	int scanX;
	int scanY;


	//ファイル名一括管理 すべてここに入力
	const char* stageFilePath[64] = {
		"./data/-_testStage4.csv",
		"./data/-_testStage2.csv",
		"./data/-_testStage3.csv",
		"./data/-_test.csv",
	};

	int pieceTexture;

	void PieceMove(const Vector2& _playerPos, const std::vector< std::vector<int>>* _field);
	//void PieceMove(const Vector2& _playerPos, const Vector2& _playerSize);

	bool HindranceBlockCheck(const std::vector< std::vector<int>>* _field,int _x,int _y);

	void Adjacent(int _pieceNum);
	void AdjacentPos(int _pieceNum1, int _pieceNum2, char _dir);
	void AdjacentPieceDelete(int _pieceNum1, int _pieceNum2);

	void DrawPieceShadow();

public:
	Piece();

	void Init(int _stageNo);
	void Update();
	void Draw();

};