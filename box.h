#pragma once

#include <Vector2.h>
#include "intVec2.h"
#include <vector>

class Box
{
public:
	Vector2 pos;
	intVec2 posInMapchip;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleraion;

	int GH;


	Box(int _x, int _y);

	void Gravity();
	void PosUpdate();
	void CollisionWithField(std::vector< std::vector<int>>* _collision);
	void CollisionWithPlayer(Vector2& _pos, const Vector2& _size, Vector2& _velo, bool& _isGround);//playgroundに移動予定
	void Update();
	void Draw();
};