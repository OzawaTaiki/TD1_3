#include "box.h"
#include "definition.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>

void Box::Gravity()
{
	velocity.y += acceleraion.y;
}

void Box::PosUpdate()
{
	pos.x += velocity.x;
	pos.y += velocity.y;

	posInMapchip.x = (int)pos.x / kTileSize;
	posInMapchip.y = (int)pos.y / kTileSize;
}

void Box::CollisionWithField(std::vector<std::vector<int>>* _collision)
{
	if (((*_collision)[int(pos.y - size.y / 2) / kTileSize][int(pos.x + velocity.x - size.x / 2) / kTileSize] == 1 ||
		(*_collision)[int(pos.y - size.y / 2) / kTileSize][int(pos.x + velocity.x - size.x / 2) / kTileSize] == 2) &&
		velocity.x < 0)
	{
		pos.x = (int(pos.x + velocity.x - size.x / 2) / kTileSize + 1) * kTileSize + size.x / 2;
		velocity.x = 0;
	}

	if (((*_collision)[int(pos.y - size.y / 2) / kTileSize][int(pos.x + velocity.x + size.x / 2 - 1) / kTileSize] == 1 ||
		(*_collision)[int(pos.y - size.y / 2) / kTileSize][int(pos.x + velocity.x + size.x / 2 - 1) / kTileSize] == 2) &&
		velocity.x > 0)
	{
		pos.x = (int(pos.x + velocity.x + size.x / 2 - 1) / kTileSize) * kTileSize - size.x / 2;
		velocity.x = 0;
	}

	if (((*_collision)[int(pos.y + velocity.y + size.y / 2 - 1) / kTileSize][int(pos.x) / kTileSize] == 1 ||
		(*_collision)[int(pos.y + velocity.y + size.y / 2 - 1) / kTileSize][int(pos.x) / kTileSize] == 2) &&
		velocity.y > 0)
	{
		pos.y = (int(pos.y + velocity.y + size.y / 2) / kTileSize) * kTileSize - size.y / 2;
		velocity.y = 0;
	}
}

Box::Box(int _x, int _y)
{
	posInMapchip = { _x,_y };
	size = { 64,64 };
	velocity = { 0,0 };
	acceleraion = { 0,0.5f };

	pos = { posInMapchip.x * kTileSize + size.x / 2.0f ,posInMapchip.y * kTileSize + size.y / 2.0f };

	GH = Novice::LoadTexture("white1x1.png");
}

void Box::CollisionWithPlayer(Vector2& _pos, const Vector2& _size, Vector2& _velo,bool& _isGround)
{
	Vector2 localpPos = { _pos.x + _velo.x,_pos.y + _velo.y };

	if (localpPos.x - _size.x / 2 <= pos.x + size.x / 2 - 1 &&
		localpPos.x + _size.x / 2 - 1 >= pos.x - size.x / 2 &&
		localpPos.y - _size.y / 2 <= pos.y + size.y / 2 - 1 &&
		localpPos.y + _size.y / 2 - 1 >= pos.y - size.y / 2)
	{
		if (_pos.y < pos.y)
		{
			_pos.y = pos.y - size.y / 2.0f - _size.y / 2.0f;
			_isGround = true;
			_velo.y = 0;
		}
		/// 左からぶつかってきてたら
		else if (_pos.x < pos.x)
		{
			velocity.x += kTileSize;
			_pos.x = pos.x - size.x / 2.0f - _size.x / 2.0f;
			_velo.x = 0;
		}
		/// 右から
		else if (_pos.x > pos.x)
		{
			velocity.x -= kTileSize;
			_pos.x = pos.x + size.x / 2.0f + _size.x / 2.0f;
			_velo.x = 0;
		}
	}
}

void Box::Update()
{
	velocity.x = 0;
	Gravity();
	//CollisionWithField(_collision);
	//PosUpdate();
}

void Box::Draw()
{
	Phill::DrawQuadPlus(int(pos.x), int(pos.y), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 63, 63, GH, 0xc03030ff, PhillDrawMode::DrawMode_Center);
	//Novice::DrawSprite(int(pos.x), int(pos.y), GH, size.x, size.y, 0, 0xc03030ff);
}
