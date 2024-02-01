#include "box.h"
#include "definition.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>

void Box::Gravity()
{
	velocity.y += acceleraion.y;
	moveDir.y = 1;
}

bool Box::CanMove(std::vector< std::vector<int>>* _field, const Vector2& _dir)
{
	if ((*_field)[posInMapchip.y + (int)_dir.y][posInMapchip.x + (int)_dir.x] == AIR)
		return true;
	return false;
}

void Box::PosUpdate()
{
	if (!isdAddVelo)
	{
		pos.x += velocity.x;
		pos.y += velocity.y;
		isdAddVelo = true;
	}

	posInMapchip.x = (int)pos.x / kTileSize;
	posInMapchip.y = (int)pos.y / kTileSize;
}

void Box::MoveDirUpdate()
{
	moveDir = { 0,0 };
	if (velocity.x < 0)
		moveDir.x = -1;
	else if (velocity.x > 0)
		moveDir.x = 1;

	if (velocity.y < 0)
		moveDir.y = -1;
	else if (velocity.y > 1)
		moveDir.y = 1;
}

void Box::Clamp()
{
	if (pos.x + velocity.x < size.x / 2 || pos.x + velocity.x >= kStageAreaWidth - size.x / 2)
	{
		if (pos.x + velocity.x < size.x / 2)
			velocity.x = size.x / 2 - pos.x;
		else if (pos.x + velocity.x >= kStageAreaWidth - size.x / 2)
			velocity.x = (kStageAreaWidth - size.x / 2) - pos.x;

		pos.x += velocity.x;
		isLockedX = true;
	}

	if (pos.y + velocity.y < size.y / 2 || pos.y + velocity.y >= kStageAreaHeight - size.y / 2)
	{
		if (pos.y + velocity.y < size.y / 2)
			velocity.y = size.y / 2 - pos.y;
		else if (pos.y + velocity.y >= kStageAreaHeight - size.y / 2)
		{
			isDraw = false;
			velocity.y = 0;
		}

		if (velocity.y > kMaxVeloY)
			velocity.y = kMaxVeloY;
		pos.y += velocity.y;
		isLockedY = true;
	}

}


Box::Box(int _x, int _y)
{
	posInMapchip = { _x,_y };
	size = { 64,64 };
	velocity = { 0,0 };
	acceleraion = { 0,0.5f };

	pos = { posInMapchip.x * kTileSize + size.x / 2.0f ,posInMapchip.y * kTileSize + size.y / 2.0f };

	vertex[0] = { -size.x / 2,-size.y / 2 };
	vertex[1] = { size.x / 2 - 1,-size.y / 2 };
	vertex[2] = { -size.x / 2,size.y / 2 - 1 };
	vertex[3] = { size.x / 2 - 1,size.y / 2 - 1 };
	isDraw = true;
	isOnPlayer = false;
	isOnBox = -1;
	isdAddVelo = false;
	isLockedX = false;
	isLockedY = false;
	GH = Novice::LoadTexture("white1x1.png");
}

void Box::Update()
{
	if (!isDraw)
		return;
	isdAddVelo = false;
	isOnPlayer = false; 
	isOnBox = -1;
	isLockedX = false;
	isLockedY = false;
	velocity.x = 0;
	MoveDirUpdate();
	Gravity();
	Clamp();
	//CollisionWithField(_collision);
	//PosUpdate();
}

void Box::Draw(int _num)
{
	if (!isDraw)
		return;
	Phill::DrawQuadPlus(int(pos.x), int(pos.y), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 63, 63, GH, 0xc03030ff, PhillDrawMode::DrawMode_Center);
	Novice::ScreenPrintf(int(pos.x - 30), int(pos.y - 10), "%d", _num);
	Novice::ScreenPrintf(int(pos.x - 30), int(pos.y + 10), "%d,%d", int(pos.x), int(pos.y));
	//Novice::DrawSprite(int(pos.x), int(pos.y), GH, size.x, size.y, 0, 0xc03030ff);
}
