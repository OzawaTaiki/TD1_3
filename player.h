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
	intVec2 drawSize;
	int drawDir;

	Vector2 vertex[4];

	const float kMoveSpd = 7.0f;
	const float kJumpVelocity = -12.0f;
	const float kMaxVeloY = 15.0f;


	int cntUp;
	const int kGoNextCnt = 15;
	int animationCurrentIndex;
	const int kAnimationIndex = 4;
	bool isAnimation;

	bool isAlive;
	bool isGround;
	bool isOnBox;
	bool isAddVelo;

	unsigned int color;

	intVec2 startPos[10] = {
		{3,10},
		{2,12},
		{2,11},
		{2,8},
		{2,4},//5
		{8,8},
		{2,2},
		{3,10},
		{2,6},
		{2,1}
	};

	int playerTexture;

	Sound* moveSound;
	Sound* jumpSound;

	void Move(const char* _keys, const char* _preKeys, int _isHave);
	void Jump(const char* _keys, const char* _preKeys, int _isHave);
	void Gravity();
	void PosUpdate();
	void MoveDirUpdate();
	void Clamp();


	Player();

	void Init(int _stageNo);
	void Update(const char* _keys, const char* _preKeys, int _isHave);
	void Draw(bool _isOverlap);
};