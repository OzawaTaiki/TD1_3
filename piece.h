﻿#pragma once

#include <Vector2.h>
#include <vector>
#include "intVec2.h"
#include "definition.h"

class Box;

class Piece
{
public:
	std::vector<std::vector<std::vector<int>>>* piece;
	std::vector<Vector2> pos;
	std::vector<Vector2> size;
	std::vector<float> scale;
	std::vector<Vector2> velocity;
	std::vector<Vector2> moveDir;

	const float kKeyScale[2] = {
		1.0f,0.6f
	};

	/// 隣接部関連
	const Vector2 kAdjacencyCheckSize = { 16,16 };
	std::vector<std::vector<Vector2>> adjacencyCheckVertex;
	std::vector<intVec2> adjacentPos;		//ピースが隣接してるときの左or上の座標
	std::vector<char> adjacentDir;
	const int kAdjacentNum = 2;

	Vector2 p2mSub;							// マウスとpiecePosの差
	Vector2 piecePrePos;					// pieceの前の座標

	Vector2 mapchipKeyPos;

	/// piece初期位置
	const Vector2 kPieceStartKeyPos = { kStageAreaWidth + 50.0f,65.0f };			// pieceの初期基準座標
	const Vector2 kPieceStartMargin = { 0.0f,260.0f };								// pieceの初期位置間隔

	int isHave;								// piece所持フラグ -1:もってない 0~:番号のピース所持
	int runX;
	int runY;

	bool canMoveX;
	bool canMoveY;

	int pieceTexture;

	bool isLockedY;

	void PieceMove(const Vector2& _playerPos, const Vector2* _playerVertex, std::vector<Box*> _box, std::vector<intVec2> _hindrancePos, const Vector2* _hindVertex);

	bool HindranceBlockCheck(const std::vector< std::vector<int>>* _field, int _x, int _y);

	void Adjacent(int _pieceNum);
	void AdjacentPos(int _pieceNum1, int _pieceNum2, char _dir);
	void AdjacentPieceDelete(int _pieceNum1, int _pieceNum2);

	int PixelCollisionWithObj(const Vector2& _pos, const Vector2* _vertex, Vector2& _collisionDir);
	int PixelCollisionWithObj(const Vector2& _pos, const Vector2* _vertex, const Vector2& _moveDir, Vector2& _collisionDir);
	int PixelCollisionWithObjOutSide(const Vector2& _pos, const Vector2* _vertex, Vector2& _collisionDir);

	Piece();

	bool IsInPiece(const Vector2& _pos, int _pieceNum);
	bool IsOverlap(const Vector2& _pos, const Vector2* _vertex, int _pieceNum);

	void MoveOnCollision(const Vector2& _collisionDir, int _collidedNum, const Vector2& _velocity);
	void CollisionPieceWithPiece();

	void PiecePosInit(int _x, int _y);
	void Init();
	void Update(const Vector2& _playerPos, const Vector2* _playerVertex, std::vector<Box*> _box, std::vector<intVec2> _hindrancePos, const Vector2* _hindVertex);
	void Draw(int _scrollY);

};