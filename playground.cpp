#include "playground.h"

#include "PhilliaFunction/Phill.h"	
#include "CSVLoader.h"
#include <Novice.h>
#include "definition.h"

#include "piece.h"
#include "player.h"
#include "box.h"


void Playground::CollisionWithPlayer()
{
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


}

void Playground::CollisionWithBox()
{

}

void Playground::PiecePlayerCollision()
{
	Vector2 collisionDir = { 0,0 };
	int collidedNum = -1;

	if (((*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.x < 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[2].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[0].x) / kTileSize + 1) * kTileSize + player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.x > 0)
	{
		collisionDir.x = player->moveDir.x;
		collidedNum =
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->velocity.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.x = (int(player->pos.x + player->velocity.x + player->vertex[1].x) / kTileSize) * kTileSize - player->size.x / 2;
			player->velocity.x = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.y < 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[0].y) / kTileSize + 1) * kTileSize + player->size.y / 2;
			player->velocity.y = 0;
		}
	}
	if (((*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= kTileKinds ||
		(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] >= kTileKinds) &&
		player->moveDir.y > 0)
	{
		collisionDir.y = player->moveDir.y;
		collidedNum =
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] >= kTileKinds ?
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] :
			(*collision)[int(player->pos.y + player->velocity.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize];

		if (piece->IsInPiece(int(player->pos.x) / kTileSize, int(player->pos.y) / kTileSize, collidedNum - kTileKinds))
			piece->MoveOnCollision(collisionDir, collidedNum);
		else
		{
			player->pos.y = (int(player->pos.y + player->velocity.y + player->vertex[2].y) / kTileSize) * kTileSize - player->size.y / 2;
			player->velocity.y = 0;
			player->isGround = true;
		}
	}
}


void Playground::GoalCheck()
{
	if (
		(*collision)[int(player->pos.y) / kTileSize][int(player->pos.x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[0].y) / kTileSize][int(player->pos.x + player->vertex[0].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[1].y) / kTileSize][int(player->pos.x + player->vertex[1].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[2].y) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] == 2 ||
		(*collision)[int(player->pos.y + player->vertex[3].y) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] == 2
		)
	{
		isClear = true;
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

	box.clear();

	for (int y = 0; y < field->size(); y++)
	{
		for (int x = 0; x < field->size(); x++)
		{
			if ((*field)[y][x] == 4)
			{
				box.push_back(new Box(x, y));
				(*field)[y][x] = 0;
			}
			else (*collision)[y][x] = (*field)[y][x];
		}
	}

	isClear = false;

	piece->Init();
	player->Init();
}

void Playground::Update(const char* _keys, const char* _preKeys)
{
	collision->clear();
	collision = new std::vector<std::vector<int>>(*field);

	piece->Update(field, collision, player->pos);
	for (int i = 0; i < box.size(); i++)
		//if (_keys[DIK_SPACE] && !_preKeys[DIK_SPACE])
		box[i]->Update();
	player->Update(_keys, _preKeys);

	CollisionWithPlayer();
	PiecePlayerCollision();
	for (int i = 0; i < box.size(); i++)
	{
		box[i]->CollisionWithPlayer(player->pos, player->size, player->velocity, player->isGround);
		box[i]->CollisionWithField(collision);
		box[i]->PosUpdate();
	}

	player->PosUpdate();

	if ((*collision)[int(player->pos.y + player->vertex[2].y + 1) / kTileSize][int(player->pos.x + player->vertex[2].x) / kTileSize] != 0 ||
		(*collision)[int(player->pos.y + player->vertex[3].y + 1) / kTileSize][int(player->pos.x + player->vertex[3].x) / kTileSize] != 0)
	{
		player->isGround = true;
	}
	else player->isGround = false;
	//無駄なことしてる自覚はあるが現状これしか思いつかないので
	for (int i = 0; i < box.size(); i++)
	{
		if (player->pos.x - player->size.x / 2 < box[i]->pos.x + box[i]->size.x / 2 - 1 &&
			player->pos.x + player->size.x / 2 - 1 > box[i]->pos.x - box[i]->size.x / 2)
		{
			if ((player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) <= 0&&
				(player->pos.y + player->size.y / 2 - 1) - (box[i]->pos.y - box[i]->size.y / 2) >= -1.5f)
				player->isGround = true;

		}
	}
	GoalCheck();

	if (isClear)
	{
		selectStage++;
		if (selectStage >= kMaxStage)
			selectStage = 0;
		Init(selectStage);
	}
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

	for (int i = 0; i < box.size(); i++)
		box[i]->Draw();
	piece->Draw();
	player->Draw();
}
