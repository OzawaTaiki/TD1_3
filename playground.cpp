#include "playground.h"

#include "PhilliaFunction/Phill.h"	
#include "CSVLoader.h"
#include <Novice.h>
#include "definition.h"

#include "piece.h"
#include "player.h"


void Playground::Collision()
{

#pragma region	field(動かないブロックたち)との衝突判定

	if (((*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] == 1) &&
		player->moveDir.x < 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] == 1) &&
		player->moveDir.x > 0)
	{
		player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
		player->velocity.x = 0;
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 1) &&
		player->moveDir.y < 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
		player->velocity.y = 0;
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 1) &&
		player->moveDir.y > 0)
	{
		player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
		player->velocity.y = 0;
		player->isGround = true;
	}

	player->PosUpdate();

	if ((*collision)[int(player->pos.y + player->vertex[2].y + 1) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 1 ||
		(*collision)[int(player->pos.y + player->vertex[3].y + 1) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 1)
	{
		player->isGround = true;
	}
	else player->isGround = false;

#pragma endregion

#pragma region	ピースとの衝突判定

	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;

	if (((*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= 2 ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] >= 2) &&
		player->moveDir.x < 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= 2 ?
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - 2))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= 2 ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] >= 2) &&
		player->moveDir.x > 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= 2 ?
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - 2))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= 2 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] >= 2) &&
		player->moveDir.y < 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= 2 ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - 2))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
			player->velocity.y = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= 2 ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] >= 2) &&
		player->moveDir.y > 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= 2 ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - 2))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
			player->velocity.y = 0;
			player->isGround = true;
		}
	}


}

Playground::Playground()
{
	piece = new Piece;
	player = new Player;

	blockTexture = Novice::LoadTexture("./img/block.png");
	goalTexture = Novice::LoadTexture("./img/goal.png");
	obstacleTexture = Novice::LoadTexture("./img/obstacleBlock.png");
}

void Playground::Init(int _stageNo)
{
	CSV_Loader::LoadFromCSV_s(stageFilePath[_stageNo], '\n');
	selectStage = _stageNo;

	field = CSV_Loader::GetPointerMapchip();
	collision = new std::vector<std::vector<int>>(*field);

	for (int y = 0; y < field->size(); y++)
	{
		for (int x = 0; x < field->size(); x++)
		{
			(*collision)[y][x] = (*field)[y][x];
		}
	}

	piece->Init();
	player->Init();
}

void Playground::Update(const char* _keys, const char* _preKeys)
{
	collision->clear();
	collision = new std::vector<std::vector<int>>(*field);


	piece->Update(field, collision, player->pos);
	player->Update(_keys, _preKeys);

	Collision();
}

void Playground::Draw()
{
	for (int y = 0; y < (*field).size(); y++)
	{
		for (int x = 0; x < (*field)[y].size(); x++)
		{
			if ((*field)[y][x] != 9)
			{

				if ((*field)[y][x] != 9 && (*field)[y][x] != 2)
					Novice::DrawBox(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 0, kTileColor_[(*field)[y][x]], kFillModeSolid);
				if ((*field)[y][x] == 1)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 7 * 64, 0, 64, 64, blockTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				if ((*field)[y][x] == 2)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, goalTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);

				if ((*field)[y][x] == 3)
					Phill::DrawQuadPlus(int(+x * kTileSize), int(+y * kTileSize), kTileSize - 1, kTileSize - 1, 1.0f, 1.0f, 0.0f, 0, 0, 64, 64, obstacleTexture, 0xffffffff, PhillDrawMode::DrawMode_LeftTop);
			}
			Novice::ScreenPrintf(1000 + x * 20, y * 20, "%d", (*collision)[y][x]);

		}
	}

	piece->Draw();
	player->Draw();
}
