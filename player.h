#pragma once
#include <Vector2.h>
#include "intVec2.h"
#include <vector>


class Player
{
public:
	Vector2 pos;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleratiion;
	Vector2 moveDir;

	Vector2 vertex[4];

	const float kMoveSpd = 7.0f;
	const float kJumpVelocity = -15.0f;

	bool isAlive;
	bool isGround;

	int GH;

	void Move(const char* _keys);
	void Jump(const char* _keys, const char* _preKeys);
	void Gravity();
	void PosUpdate();
	void MoveDirUpdate();


	Player();

	void Init();
	void Update(const char* _keys, const char* _preKeys);
	void Draw();
};