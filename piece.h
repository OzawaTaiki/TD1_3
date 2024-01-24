#pragma once

#include <Vector2.h>
#include <vector>
#include "intVec2.h"
#include "definition.h"

class Piece
{
public:
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

	Vector2 moveDir;

	/// piece初期位置
	const Vector2 kPieceStartKeyPos = { kStageAreaWidth + 50.0f,65.0f };			// pieceの初期基準座標
	const Vector2 kPieceStartMargin = { 0.0f,260.0f };				// pieceの初期位置間隔

	int isHave;								// piece所持フラグ -1:もってない 0~:番号のピース所持



	int scanX;
	int scanY;

	int pieceTexture;

	void PieceMove(const std::vector< std::vector<int>>* _field, const Vector2& _playerPos);
	//void PieceMove(const Vector2& _playerPos, const Vector2& _playerSize);


	bool HindranceBlockCheck(const std::vector< std::vector<int>>* _field, int _x, int _y);

	void Adjacent(int _pieceNum);
	void AdjacentPos(int _pieceNum1, int _pieceNum2, char _dir);
	void AdjacentPieceDelete(int _pieceNum1, int _pieceNum2);

	void FieldCollision(std::vector< std::vector<int>>* _collision);

	void DrawPieceShadow();


	Piece();

	/// <param name="_checkX">判定する対象のｘ座標</param>
	/// <param name="_checkY">判定する対象のｙ座標</param>
	/// <param name="_pieceNum">判定するピースの番号 0~</param>
	/// <returns></returns>
	bool IsInPiece(int _checkX, int _checkY, int _pieceNum);

	/// <param name="collisionDir">ぶつかった向き -1,0,1 片方０ </param>
	/// <param name="collidedNum">衝突した番号</param>
	void MoveOnCollision(const Vector2& _collisionDir, int _collidedNum);

	void PiecePosInit(int _x, int _y);
	void Init();
	void Update(const std::vector< std::vector<int>>* _field, std::vector< std::vector<int>>* _collision, const Vector2& _playerPos);
	void Draw();

};