#include "player.h"

#include "PhilliaFunction/Phill.h"
#include <Novice.h>

void Player::Move(const char* _keys)
{
	int moveX = 0;

	if (_keys[DIK_A])
		moveX = -1;
	if (_keys[DIK_D])
		moveX = 1;

	velocity.x = moveX * kMoveSpd;
}

void Player::Jump(const char* _keys, const char* _preKeys)
{
	if (_keys[DIK_W] && !_preKeys[DIK_W] && isGround)
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
	else if (velocity.y > 0)
		moveDir.x = 1;

	if (velocity.y < 0)
		moveDir.y = -1;
	else if (velocity.y > 0)
		moveDir.y = 1;
}

Player::Player()
{
	pos = { 64,64 };
	size = { 40,40 };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };

	isAlive = true;
	isGround = false;

	GH = Novice::LoadTexture("./img/player.png");
}

void Player::PosUpdate()
{
	pos.x += velocity.x;
	pos.y += velocity.y;
}

void Player::Init()
{
	pos = { 64,64 };
	size = { 40,40 };
	velocity = { 0,0 };
	acceleratiion = { 0,0.5f };
	moveDir = { 0,0 };

	isAlive = true;
	isGround = false;
}

void Player::Update(const char* _keys, const char* _preKeys)
{
	Move(_keys);
	Jump(_keys, _preKeys);
	if (!isGround)
		Gravity();
	PosUpdate();
	MoveDirUpdate();
}

void Player::Draw()
{
	Phill::DrawQuadPlus(int(pos.x), int(pos.y), int(size.x), int(size.y), 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, GH, 0xffffffff, PhillDrawMode::DrawMode_Center);
}
