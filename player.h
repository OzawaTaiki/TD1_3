#pragma once
#include <Vector2.h>
#include "intVec2.h"
#include <vector>
#include "sound.h"


class Player
{
public:
	Vector2 pos;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleratiion;
	Vector2 moveDir;
	intVec2 GHSize;


	Vector2 vertex[4];

	const float kMoveSpd = 7.0f;
	const float kJumpVelocity = -12.0f;
	const float kMaxVeloY = 15.0f;

	bool isAlive;
	bool isGround;
	bool isOnBox;
	bool isAddVelo;

	intVec2 startPos[10] = {
		{3,10},
		{2,12},
		{1,11},
		{1,8},
		{7,7},
		{2,11},
		{1,11},
		{1,2},
		{1,10},
		{2,11}
	};

	int playerTexture;

	Sound* moveSound;
	Sound* jumpSound;

	void Move(const char* _keys , const char* _preKeys);
	void Jump(const char* _keys, const char* _preKeys);
	void Gravity();
	void PosUpdate();
	void MoveDirUpdate();
	void Clamp();


	Player();

	void Init(int _stageNo);
	void Update(const char* _keys, const char* _preKeys);
	void Draw();
};