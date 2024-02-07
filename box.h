#pragma once

#include <Vector2.h>
#include "intVec2.h"
#include <vector>
#include "sound.h"


class Box
{
public:
	Vector2 pos;
	intVec2 posInMapchip;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleraion;
	Vector2 moveDir;

	Vector2 vertex[4];


	const float kMaxVeloY = 15.0f;
	int boxTextrue;
	int isOnBox;
	unsigned int color;

	bool isOnPlayer;
	bool isLockedX;
	bool isLockedY;
	bool isDraw;
	bool isdAddVelo;

	Sound* moveSound;

	Box(int _x, int _y);

	void Gravity();
	bool CanMove(std::vector< std::vector<int>>* _field, const Vector2& _dir);
	void PosUpdate();
	void MoveDirUpdate();
	void Clamp();

	//void CollisionWithField(std::vector< std::vector<int>>* _collision);
	//void CollisionWithPlayer(Vector2& _pos, const Vector2& _size, Vector2& _velo, bool& _isGround);//playgroundに移動予定
	void Update();
	void Draw(int _num, int warningVisible);
};