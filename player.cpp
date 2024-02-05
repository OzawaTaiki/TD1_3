#include "player.h"

#include "PhilliaFunction/Phill.h"
#include <Novice.h>
#include "definition.h"

void Player::Move(const char* _keys, const char* _preKeys)
{
	int moveX = 0;
	if (_keys[DIK_LSHIFT])
	{
		if (_keys[DIK_A] && !_preKeys[DIK_A])
			moveX = -1;
		if (_keys[DIK_D] && !_preKeys[DIK_D])
			moveX = 1;
	}
	else
	{
		if (_keys[DIK_A])
			moveX = -1;
		if (_keys[DIK_D])
			moveX = 1;
	}

	velocity.x = moveX * kMoveSpd;
}

void Player::Jump(const char* _keys, const char* _preKeys)
{
	if ((_keys[DIK_W] /*&& !_preKeys[DIK_W]*/ || _keys[DIK_SPACE] && !_preKeys[DIK_SPACE]) && isGround)
	{
		velocity.y = kJumpVelocity;
		isGround = false;
	}
}

void Player::Gravity()
{
	velocity.y += acceleratiion.y;
}

void Player::MoveDirUpdate()
{
	moveDir = { 0,0 };
	if (velocity.x < 0)
		moveDir.x = -1;
	else if (velocity.x > 0)
		moveDir.x = 1;

	if (velocity.y < 0)
		moveDir.y = -1;
	else if (velocity.y > 0)
		moveDir.y = 1;
}

void Player::Clamp()
{
	if (pos.x + velocity.x < size.x / 2)
		velocity.x = size.x / 2 - pos.x;
	if (pos.x + velocity.x >= kStageAreaWidth - size.x / 2)
		velocity.x = pos.x - (kStageAreaWidth - size.x / 2);
	if (pos.y + velocity.y < size.y / 2)
		velocity.y = size.y / 2 - pos.y;
	if (pos.y + velocity.y >= kStageAreaHeight - size.y / 2)
	{
		velocity.y = 0;
		isAlive = false;
	}

	if (velocity.y > kMaxVeloY)
		velocity.y = kMaxVeloY;
}

Player::Player()
{
	pos = { 64,64 };
	size = { 64,96 };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };

	isAlive = true;
	isGround = false;
	isOnBox=false;
	isAddVelo = false;

	vertex[0] = { -size.x / 2,-size.y / 2 };
	vertex[1] = { size.x / 2 - 1,-size.y / 2 };
	vertex[2] = { -size.x / 2,size.y / 2 - 1 };
	vertex[3] = { size.x / 2 - 1,size.y / 2 - 1 };

	GH = Novice::LoadTexture("./Resources/img/player.png");
}

void Player::PosUpdate()
{
	if (!isAddVelo)
	{
		pos.x += velocity.x;
		pos.y += velocity.y;
		isAddVelo = true;
	}
}

void Player::Init(int _stageNo)
{
	pos = { float(startPos[_stageNo].x * kTileSize + kTileSize / 2),float(startPos[_stageNo].y * kTileSize + kTileSize / 2) };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };

	isAlive = true;
	isGround = false;
}

void Player::Update(const char* _keys, const char* _preKeys)
{
	isOnBox = false;
	isAddVelo = false;

	Move(_keys, _preKeys);
	Jump(_keys, _preKeys);
	Gravity();
	Clamp();
	MoveDirUpdate();
}

void Player::Draw()
{
	Phill::DrawQuadPlus(int(pos.x), int(pos.y), int(size.x), int(size.y), 1.0f, 1.0f, 0.0f, 0, 0, int(size.x), int(size.y), GH, 0xffffffff, PhillDrawMode::DrawMode_Center);

	//Novice::ScreenPrintf(int(pos.x - 20), int(pos.y - 40), "%d,%d", int(pos.x), int(pos.y));
	/*for (int i = 0; i < 4; i++)
	{
		Novice::ScreenPrintf(1600, 900 + i * 20, "%.1f,%.1f", pos.x + vertex[i].x, pos.y + vertex[i].y);
		Novice::ScreenPrintf(1720, 900 + i * 20, "%d,%d", int(pos.x + vertex[i].x) / kTileSize, int(pos.y + vertex[i].y) / kTileSize);
	}*/
}
